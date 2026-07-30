/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbentes- <kbentes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 21:38:41 by kbentes-          #+#    #+#             */
/*   Updated: 2026/07/29 22:44:45 by kbentes-         ###   ########.fr       */
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

typedef struct s_dongle
{
	int				id;
	pthread_mutex_t	mutex;
}	t_dongle;

typedef struct s_coder
{
	int			id;
	int			compiles_done;
	pthread_t	thread;
	t_dongle	*left_dongle;
	t_dongle	*right_dongle;
	t_program	*program;
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
	t_config	config;
	t_coder		*coders;
	t_dongle	*dongles;
	long long	start_time;
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
void		destroy_program(t_program *program);

/* time */
void		smart_sleep(long long ms);
long long	get_time_ms(void);
long long	get_elapsed_ms(long long start);

/* logger */
void		log_event(t_program *program, int coder_id, t_state state);

/* coder */
void		*coder_routine(void *arg);

/* threads */
int			create_threads(t_program *program);
int			join_threads(t_program *program);

/* init */
int			init_dongles(t_program *program);
int			init_coders(t_program *program);
int			init_program(t_program *program, t_config *config);

/* destroy */
void		destroy_dongles(t_program *program, int count);
void		destroy_program(t_program *program);

#endif
