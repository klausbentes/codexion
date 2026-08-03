/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbentes- <kbentes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 21:38:41 by kbentes-          #+#    #+#             */
/*   Updated: 2026/08/03 19:17:14 by kbentes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CODEXION_H
# define CODEXION_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <limits.h>
# include <sys/time.h>
# include <pthread.h>
# include <time.h>

# define FIFO_SCHED 0
# define EDF_SCHED 1

typedef struct s_config
{
	int		number_of_coders;
	long	time_to_burnout;
	long	time_to_compile;
	long	time_to_debug;
	long	time_to_refactor;
	int		number_of_compiles_required;
	long	dongle_cooldown;
	int		scheduler;
}	t_config;

typedef struct s_program	t_program;

typedef struct s_request
{
	int			coder_id;
	long long	key;
	long long	seq;
}	t_request;

typedef struct s_heap
{
	t_request	*items;
	int			size;
	int			capacity;
}	t_heap;

typedef struct s_dongle
{
	int				id;
	pthread_mutex_t	mutex;
	pthread_cond_t	cond;
	int				locked;
	long long		next_seq;
	long long		released_at;
	t_heap			queue;
}	t_dongle;

typedef struct s_coder
{
	int				id;
	int				compiles_done;
	pthread_t		thread;
	pthread_mutex_t	activity_mutex;
	long long		last_compile_start;
	t_dongle		*left_dongle;
	t_dongle		*right_dongle;
	t_program		*program;
}	t_coder;

typedef enum e_state
{
	STATE_TAKEN_DONGLE,
	STATE_COMPILING,
	STATE_DEBUGGING,
	STATE_REFACTORING,
	STATE_BURNED_OUT
}	t_state;

struct s_program
{
	t_config		config;
	t_coder			*coders;
	t_dongle		*dongles;
	long long		start_time;
	pthread_t		monitor_thread;
	pthread_mutex_t	state_mutex;
	pthread_mutex_t	log_mutex;
	int				stopped;
};

/* parser */
int			is_all_digits(const char *str);
long		str_to_long(const char *str, int *err);
int			check_scheduler(const char *str);
int			parse_positive(const char *str, long *out);
int			fill_config(char **argv, t_config *cfg);
int			parse_args(int argc, char **argv, t_config *cfg);
void		print_usage(void);
int			print_error(const char *msg);

/* init */
int			init_dongles(t_program *program);
int			init_coders(t_program *program);
int			init_program(t_program *program, t_config *config);

/* destroy */
void		destroy_dongles(t_program *program, int count);
void		destroy_coders(t_program *program, int count);
void		destroy_program(t_program *program);

/* time */
void		smart_sleep(long long ms);
long long	get_time_ms(void);
long long	get_elapsed_ms(long long start);

/* logger */
void		log_event(t_program *program, int coder_id, t_state state);

/* coder */
void		*coder_routine(void *arg);
void		update_last_compile_start(t_coder *coder);
long long	get_last_compile_start(t_coder *coder);

/* coder dongles */
int			acquire_dongles(t_coder *coder);
void		release_dongles(t_coder *coder);
int			acquire_pair(t_dongle *first, t_dongle *second, t_coder *coder);
void		release_pair(t_dongle *first, t_dongle *second);

/* state */
int			is_simulation_stopped(t_program *program);
void		stop_simulation(t_program *program);

/* monitor */
void		*monitor_routine(void *arg);

/* threads */
int			create_threads(t_program *program);
int			create_monitor(t_program *program);
int			join_threads(t_program *program);
int			join_monitor(t_program *program);

/* init */
int			init_dongles(t_program *program);
int			init_coders(t_program *program);
int			init_program(t_program *program, t_config *config);

/* destroy */
void		destroy_dongles(t_program *program, int count);
void		destroy_program(t_program *program);

/* heap */
int			heap_init(t_heap *heap, int capacity);
void		heap_destroy(t_heap *heap);
void		heap_push(t_heap *heap, t_request request);
t_request	heap_pop(t_heap *heap);
int			heap_peek_id(t_heap *heap);
void		heap_remove_id(t_heap *heap, int coder_id);
void		sift_up(t_heap *heap, int index);
void		sift_down(t_heap *heap, int index);
void		swap_requests(t_request *a, t_request *b);
int			request_less(t_request *a, t_request *b);

/* time */
long long	get_time_ms(void);
long long	get_elapsed_ms(long long start);
void		smart_sleep(long long ms);
void		ms_to_timespec(long long ms, struct timespec *ts);

/* dongle scheduling */
long long	get_schedule_key(t_coder *coder);
int			dongle_acquire(t_dongle *dongle, t_coder *coder,
				long long key, long cooldown);
void		dongle_release(t_dongle *dongle);
void		wake_all_dongles(t_program *program);

/* dongle cooldown */
long long	cooldown_remaining_ms(t_dongle *dongle, long cooldown);

#endif
