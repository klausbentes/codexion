/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbentes- <kbentes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 04:25:45 by kbentes-          #+#    #+#             */
/*   Updated: 2026/07/31 19:46:00 by kbentes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	init_config(t_program *program, t_config *config)
{
	program->config = *config;
}

int	init_program(t_program *program, t_config *config)
{
	init_config(program, config);
	program->coders = NULL;
	program->dongles = NULL;
	program->stopped = 0;
	program->start_time = get_time_ms();
	if (pthread_mutex_init(&program->state_mutex, NULL) != 0)
		return (-1);
	if (init_dongles(program) == -1)
	{
		pthread_mutex_destroy(&program->state_mutex);
		return (-1);
	}
	if (init_coders(program) == -1)
	{
		pthread_mutex_destroy(&program->state_mutex);
		free(program->dongles);
		program->dongles = NULL;
		return (-1);
	}
	return (0);
}
