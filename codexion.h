/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbentes- <kbentes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 20:37:08 by kbentes-          #+#    #+#             */
/*   Updated: 2026/07/18 03:57:16 by kbentes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int		is_all_digits(const char *str);
long	str_to_long(const char *str, int *err);
int		check_scheduler(const char *str);
int		parse_positive(const char *str, long *out);
int		fill_config(char **argv, t_config *cfg);
int		parse_args(int argc, char **argv, t_config *cfg);
void	print_usage(void);
int		print_error(const char *msg);

#endif