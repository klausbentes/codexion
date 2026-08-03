/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbentes- <kbentes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 04:25:45 by kbentes-          #+#    #+#             */
/*   Updated: 2026/08/03 19:09:03 by kbentes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	init_config(t_program *program, t_config *config)
{
	program->config = *config;
}

static int	init_mutexes(t_program *program)
{
	if (pthread_mutex_init(&program->state_mutex, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&program->log_mutex, NULL) != 0)
	{
		pthread_mutex_destroy(&program->state_mutex);
		return (-1);
	}
	return (0);
}

int	init_program(t_program *program, t_config *config)
{
	init_config(program, config);
	program->coders = NULL;
	program->dongles = NULL;
	program->stopped = 0;
	program->start_time = get_time_ms();
	if (init_mutexes(program) == -1)
		return (-1);
	if (init_dongles(program) == -1)
	{
		pthread_mutex_destroy(&program->log_mutex);
		pthread_mutex_destroy(&program->state_mutex);
		return (-1);
	}
	if (init_coders(program) == -1)
	{
		pthread_mutex_destroy(&program->log_mutex);
		pthread_mutex_destroy(&program->state_mutex);
		free(program->dongles);
		program->dongles = NULL;
		return (-1);
	}
	return (0);
}
