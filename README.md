*This project has been created as part of the 42 curriculum by kbentes-.*

# Codexion

Master the race for resources before the deadline masters you.

## Table of Contents

- [Description](#description)
- [Instructions](#instructions)
- [Resources](#resources)
- [Blocking Cases Handled](#blocking-cases-handled)
- [Thread Synchronization Mechanisms](#thread-synchronization-mechanisms)
- [Project Structure](#project-structure)
- [Program Flow](#program-flow)
- [Error Handling](#error-handling)

## Description

Codexion is a C simulation of concurrent resource sharing, modeled after the
classic Dining Philosophers problem. A configurable number of **coders** sit
around a circular co-working hub, cycling endlessly through three phases:
**compile**, **debug**, and **refactor**. Compiling is the only phase that
requires a shared resource: each coder needs two **USB dongles** (one from
each neighbor) plugged in simultaneously to compile. There are exactly as
many dongles as coders, arranged so that one dongle sits between each pair
of neighboring coders.

The simulation stops under one of two conditions:

- every coder has compiled at least `number_of_compiles_required` times, or
- any single coder **burns out** — meaning it failed to start a new compile
  within `time_to_burnout` milliseconds of its last compile (or of the start
  of the simulation).

### Concurrency problems addressed

This project is fundamentally an exercise in safe concurrent resource
sharing. The implementation specifically addresses:

- **Mutual exclusion** over each dongle, so no two coders can hold the same
  dongle at once.
- **Deadlock prevention**, since the circular dongle layout is structurally
  identical to the Dining Philosophers deadlock scenario.
- **Fair arbitration** between coders competing for the same dongle, under
  two selectable policies: `fifo` and `edf`.
- **Cooldown enforcement**, delaying dongle reuse after release.
- **Precise, timely burnout detection**, performed by a dedicated monitor
  thread independent of the coder threads (which may themselves be
  blocked).
- **Serialized logging**, so concurrent state-change messages from multiple
  threads never interleave on the same line.
- **Orderly shutdown**, ensuring that once the simulation stops, no coder
  thread remains stuck waiting forever on a dongle that will never be
  granted.

### Architecture overview

The program is organized in independent layers, each with a single
responsibility:

1. **Parser** — validates and converts the 8 mandatory CLI arguments into a
   `t_config` struct.
2. **Initialization** — allocates and wires up `t_program`, `t_coder`, and
   `t_dongle`, including their mutexes, condition variables, and per-dongle
   priority queues.
3. **Time API** — a small wrapper around `gettimeofday()` exposing time
   exclusively in milliseconds (`long long`), so the rest of the codebase
   never touches `struct timeval` directly.
4. **Logger** — a single, mutex-protected function through which every
   state-change message is printed.
5. **Dongle scheduling** — a per-dongle min-heap priority queue that
   arbitrates access according to the configured scheduler (`fifo`/`edf`)
   and enforces the cooldown.
6. **Coder thread** — runs the compile/debug/refactor cycle.
7. **Monitor thread** — periodically checks for burnout and for global
   completion, and is the single authority that stops the simulation.

## Instructions

### Compilation

```bash
make
```

This produces the `codexion` binary at the project root. The Makefile
compiles all sources with `-Wall -Wextra -Werror -pthread`, using `cc`, and
supports the standard rules:

```bash
make        # build the project
make clean  # remove object files
make fclean # remove object files and the binary
make re     # fclean + all
```

### Usage

```bash
./codexion number_of_coders time_to_burnout time_to_compile time_to_debug \
           time_to_refactor number_of_compiles_required dongle_cooldown scheduler
```

All eight arguments are mandatory.

| Argument | Description |
|---|---|
| `number_of_coders` | Number of coders, and also the number of dongles. |
| `time_to_burnout` | Time (ms) a coder may go without starting a compile before burning out. |
| `time_to_compile` | Time (ms) a coder spends compiling while holding both dongles. |
| `time_to_debug` | Time (ms) a coder spends debugging. |
| `time_to_refactor` | Time (ms) a coder spends refactoring, after which it immediately tries to compile again. |
| `number_of_compiles_required` | The simulation stops once every coder has reached this many completed compiles. |
| `dongle_cooldown` | Time (ms) a dongle stays unavailable after being released. |
| `scheduler` | Arbitration policy for dongle access: exactly `fifo` or `edf`. |

All numeric arguments must be strictly positive integers (a leading `+` sign
is accepted, e.g. `+0005`). Any negative number, non-numeric input, or a
scheduler value other than `fifo`/`edf` is rejected with an error message.

### Examples

Five coders, FIFO scheduling, each must compile 3 times:

```bash
./codexion 5 800 200 100 100 3 50 fifo
```

Four coders, EDF scheduling, tighter burnout margin:

```bash
./codexion 4 600 150 100 100 5 30 edf
```

Single coder — structurally impossible to compile (compiling requires two
dongles, and only one exists), so the coder will wait, burn out after
`time_to_burnout` ms, and the simulation will stop cleanly:

```bash
./codexion 1 800 200 100 100 3 50 fifo
```

### Sample output

```
0 1 has taken a dongle
2 1 has taken a dongle
2 1 is compiling
202 1 is debugging
402 1 is refactoring
405 2 has taken a dongle
406 2 has taken a dongle
406 2 is compiling
...
1505 4 burned out
```

## Resources

### Classic references

- POSIX Threads Programming (LLNL Tutorial) — foundational overview of
  `pthread_create`, `pthread_join`, mutexes, and condition variables.
- `man 3 pthread_mutex_init`, `man 3 pthread_cond_wait`,
  `man 3 pthread_cond_timedwait` — POSIX manual pages, used as the primary
  reference for correct API usage and edge-case behavior (e.g. spurious
  wakeups, the need to re-check predicates in a loop).
- Edsger W. Dijkstra, *Dining Philosophers Problem* — the classical
  formulation of the circular resource-contention scenario this project is
  built around.
- E. G. Coffman, M. Elphick, A. Shoshani, *"System Deadlocks"* (1971) — the
  original formulation of the four necessary conditions for deadlock
  (mutual exclusion, hold and wait, no preemption, circular wait), used as
  the conceptual basis for the deadlock-prevention strategy in this
  project.
- C. L. Liu and J. Layland, *"Scheduling Algorithms for Multiprogramming in
  a Hard-Real-Time Environment"* (1973) — origin of the Earliest Deadline
  First (EDF) scheduling policy implemented here.

### AI usage

An AI assistant (Claude) was used throughout the development of this
project as a **design and review partner**, not as a source of unreviewed
code. Concretely, it was used to:

- **Discuss architecture** at each incremental step (parser, initialization,
  time API, logger, threading, mutexes, scheduling, cooldown), before any
  code was written for that step.
- **Explain concurrency concepts** in the context of this specific project
  — for example, why the naive left-then-right dongle acquisition order
  reproduces the Dining Philosophers deadlock, and why a lost-wakeup race
  can occur if a stop signal isn't broadcast under the same mutex a waiting
  thread holds.
- **Review design decisions**, such as choosing a mutex per dongle instead
  of one global mutex (for concurrency granularity), or centralizing all
  program output behind a single `log_event()` function so that only one
  place would later need synchronization.
- **Assist in writing parts of the code**, always followed by a manual
  review and, in later iterations, real test runs (including the
  single-coder edge case, which the AI-suggested first attempt did not
  handle correctly and was corrected after inspecting the actual observed
  deadlock).
- **Explain implementations after the fact**, so that every function added
  to the project could be justified in terms of the responsibility it
  encapsulates and how it interacts with the rest of the codebase.
- **Review Norm compliance**, for example refactoring `main.c` when a
  `TOO_MANY_LINES` violation was reported, and splitting files when a
  `TOO_MANY_FUNCS` violation appeared, in both cases by extracting
  functions along genuine responsibility boundaries rather than
  arbitrarily.
- **Help draft this README**, structured around the subject's explicit
  requirements and the actual state of the implementation.

All AI-assisted code was read, tested against real command-line scenarios,
and — in the case of the single-coder deadlock — debugged from an actual
observed hang rather than accepted at face value.

## Blocking Cases Handled

### Deadlock prevention and Coffman's conditions

The naive strategy — every coder acquiring its left dongle before its right
dongle — reproduces all four Coffman conditions simultaneously: mutual
exclusion (enforced by each dongle's mutex), hold-and-wait (a coder keeps
its first dongle while waiting for the second), no preemption (no thread
can force another to release a dongle), and circular wait (the circular
seating arrangement lets every coder simultaneously hold its "left" dongle
while waiting for its "right" one, which is its neighbor's "left" one).

The fix breaks the circular wait condition by breaking the symmetry: every
coder acquires left-then-right, **except the last coder**
(`id == number_of_coders`), which acquires right-then-left. This enforces a
single, consistent global ordering over dongle indices for all acquisition
attempts, which makes a closed wait cycle impossible — a classical
resource-ordering proof of deadlock freedom.

### Starvation prevention

Each dongle owns its own priority queue (a binary min-heap implemented from
scratch, as required by the subject — no standard library priority queue is
used). Two scheduling policies are supported:

- **`fifo`**: the queue key is the wall-clock time at which the request was
  made, so the dongle is always granted to the oldest pending request.
- **`edf`**: the queue key is the coder's burnout deadline
  (`last_compile_start + time_to_burnout`), so the dongle is always granted
  to whichever waiting coder is closest to burning out. As time passes, a
  coder's deadline approaches, which naturally raises its priority — this
  is what gives EDF its starvation-avoidance property under feasible
  parameters.

A monotonic per-dongle sequence number is used as a tie-breaker when two
requests share the exact same key, guaranteeing a fully deterministic
ordering in both modes.

### Dongle cooldown

Every dongle stores `released_at`, the timestamp of its last release. Before
granting a dongle, the scheduler checks `cooldown_remaining_ms()`; if the
cooldown has not yet elapsed, the requesting thread waits — using
`pthread_cond_timedwait()` bounded to the exact remaining cooldown — instead
of busy-polling.

### Precise burnout detection

Burnout detection is the sole responsibility of a dedicated **monitor
thread**, independent from every coder thread. This is necessary because a
coder that is about to burn out is, by definition, blocked (waiting on a
dongle or mid-sleep) and cannot reliably evaluate its own state. The
monitor loops with a 1 ms `smart_sleep()` between checks, comparing
`get_elapsed_ms(last_compile_start)` against `time_to_burnout` for every
coder, which keeps detection comfortably within the required 10 ms
tolerance.

### Log serialization

All program output goes through a single function, `log_event()`, which
locks a dedicated `log_mutex` around the timestamp computation and the
`printf()` call. No other function in the codebase writes simulation output
directly, so this single mutex is sufficient to guarantee that two
messages from different threads can never interleave on the same line.

### Orderly simulation shutdown

Stopping the simulation involves two coordinated steps inside
`stop_simulation()`: setting the shared `stopped` flag (under
`state_mutex`), then calling `wake_all_dongles()`, which locks each
dongle's mutex in turn and broadcasts on its condition variable. This
guarantees that any coder thread currently blocked waiting for a dongle
— including the structurally permanent wait of a single-coder simulation,
where a lone coder can never obtain a second dongle — is woken up, notices
the stop flag, releases whatever it holds, and exits cleanly instead of
leaving `pthread_join()` waiting forever.

## Thread Synchronization Mechanisms

| Mechanism | Location | Protects | Purpose |
|---|---|---|---|
| `pthread_mutex_t mutex` (per dongle) | `t_dongle` | `locked`, `released_at`, `next_seq`, the per-dongle priority queue | Serializes access to a single dongle's internal scheduling state. |
| `pthread_cond_t cond` (per dongle) | `t_dongle` | — | Lets waiting coders sleep instead of busy-polling, woken on release, cooldown expiry, or simulation stop. |
| `pthread_mutex_t activity_mutex` (per coder) | `t_coder` | `last_compile_start` | Prevents a data race between the coder thread (writer) and the monitor thread (reader). |
| `pthread_mutex_t state_mutex` | `t_program` | `stopped` | Prevents a data race on the single shared "simulation is over" flag, read by every coder and written only by the monitor. |
| `pthread_mutex_t log_mutex` | `t_program` | standard output | Serializes every `printf()` call made through `log_event()`. |

### How race conditions are prevented

- **Dongle state** is never read or written outside its own mutex. A coder
  requesting a dongle pushes a request onto that dongle's heap and then
  waits on that dongle's condition variable — both operations happen while
  holding the dongle's mutex, so the request queue can never be corrupted
  by concurrent pushes/pops from different coders.
- **`last_compile_start`** is never accessed directly; all access goes
  through `update_last_compile_start()` / `get_last_compile_start()`, both
  of which lock `activity_mutex`. This is what lets the monitor safely read
  a value that a coder thread may be writing concurrently, without risking
  a torn read.
- **The global stop flag** follows the same pattern: `is_simulation_stopped()`
  and `stop_simulation()` are the only functions that ever touch
  `program->stopped`, both under `state_mutex`.

### Coder ↔ monitor communication

Coders and the monitor never communicate directly or exchange messages —
they only share state protected by mutexes, following a
producer/observer pattern:

```
coder thread                      monitor thread
-------------                     --------------
update_last_compile_start()  -->  get_last_compile_start()
(writes, mutex-protected)         (reads, mutex-protected, every 1ms)

                                   detects burnout / all_compiled
                                   -> stop_simulation()
                                        - sets program->stopped
                                        - wake_all_dongles()
is_simulation_stopped()      <--  (read by every coder, and inside
(checked each loop iteration,      every dongle wait loop)
and inside dongle wait loops)
```

This indirection is what allows a single monitor decision to affect every
coder — including ones currently blocked on a dongle — without the coders
needing to know *why* the simulation stopped.

### Logger thread-safety

`log_event()` is the only function in the project that writes to standard
output. Every call locks `log_mutex`, computes the elapsed time, prints the
line, and unlocks — so from the perspective of any external observer,
log lines are always fully formed and never interleaved, regardless of how
many coder threads are logging concurrently. As an additional safeguard,
`log_event()` checks `is_simulation_stopped()` before printing, so no
state-change message is emitted after the simulation has already been
declared over (aside from an unavoidable, negligible-duration race between
that check and the monitor setting the flag).

## Project Structure

```
.
├── Makefile
├── README.md
├── codexion.h
└── src/
    ├── main.c                  # entry point / orchestration
    ├── parser.c                # argument count + orchestration
    ├── parser_check.c          # raw format validation (digits, sign)
    ├── parser_validate.c       # business rules (positivity, scheduler)
    ├── error.c                 # usage/error printing
    ├── init_program.c          # t_program setup
    ├── init_dongles.c          # t_dongle array + mutex/cond/heap setup
    ├── init_coders.c           # t_coder array + topology wiring
    ├── destroy.c                # teardown of all allocated resources
    ├── time.c / time_utils.c   # gettimeofday() wrapper API
    ├── logger.c                # single, mutex-protected log function
    ├── coder.c                 # compile/debug/refactor cycle
    ├── coder_dongles.c          # left/right dongle ordering
    ├── coder_dongles_pair.c     # acquire/release pair of dongles
    ├── coder_activity.c         # thread-safe last_compile_start access
    ├── state.c                  # thread-safe stopped flag
    ├── monitor.c                 # burnout + completion detection
    ├── dongle_schedule.c         # FIFO/EDF arbitration logic
    ├── dongle_cooldown.c         # cooldown timing calculation
    ├── dongle_wake.c             # broadcasts wake-up on shutdown
    ├── heap.c / heap_pop.c
    │   / heap_remove.c / heap_utils.c  # custom priority queue
    └── threads.c                 # pthread_create/join for coders + monitor
```

## Program Flow

```
main()
 └─ parse_args()            validate the 8 CLI arguments
 └─ init_program()          allocate coders, dongles, mutexes, queues
 └─ run_simulation()
     ├─ create_threads()    one thread per coder
     ├─ create_monitor()    one dedicated monitor thread
     ├─ join_threads()      wait for every coder to exit
     └─ join_monitor()      wait for the monitor to exit
 └─ destroy_program()       release every mutex, condvar, heap, and array
```

Each coder thread loops: acquire both dongles (ordered to avoid deadlock,
arbitrated by the configured scheduler, respecting cooldown) → compile →
release dongles → debug → refactor → repeat, until the monitor signals that
the simulation is over.

## Error Handling

- All eight CLI arguments are mandatory and strictly validated: malformed
  numbers, non-positive values, and an invalid scheduler string are all
  rejected with a descriptive error message and a non-zero exit code.
- Every `malloc()`, `pthread_mutex_init()`, `pthread_cond_init()`, and
  `pthread_create()` call is checked. On failure, initialization unwinds
  everything already allocated (mutexes destroyed, condition variables
  destroyed, priority queues freed, arrays freed) before returning an error,
  so no partial-initialization state is ever leaked.
- The program never calls `exit()` from deep within the logic; every
  function reports failure through its return value, and only `main()`
  decides how to react.
