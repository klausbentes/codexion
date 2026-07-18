#ifndef CODEXION_H
# define CODEXION_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <limits.h>

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
	int	id;
}	t_dongle;

typedef struct s_coder
{
	int			id;
	int			compiles_done;
	t_dongle	*left_dongle;
	t_dongle	*right_dongle;
	t_program	*program;
}	t_coder;

struct s_program
{
	t_config	config;
	t_coder		*coders;
	t_dongle	*dongles;
};

/* parser */
int		is_all_digits(const char *str);
long	str_to_long(const char *str, int *err);
int		check_scheduler(const char *str);
int		parse_positive(const char *str, long *out);
int		fill_config(char **argv, t_config *cfg);
int		parse_args(int argc, char **argv, t_config *cfg);
void	print_usage(void);
int		print_error(const char *msg);

/* init */
int		init_dongles(t_program *program);
int		init_coders(t_program *program);
int		init_program(t_program *program, t_config *config);

/* destroy */
void	destroy_program(t_program *program);

#endif