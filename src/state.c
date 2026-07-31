/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbentes- <kbentes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 19:44:49 by kbentes-          #+#    #+#             */
/*   Updated: 2026/07/31 19:44:51 by kbentes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	is_simulation_stopped(t_program *program)
{
	int	stopped;

	pthread_mutex_lock(&program->state_mutex);
	stopped = program->stopped;
	pthread_mutex_unlock(&program->state_mutex);
	return (stopped);
}

void	stop_simulation(t_program *program)
{
	pthread_mutex_lock(&program->state_mutex);
	program->stopped = 1;
	pthread_mutex_unlock(&program->state_mutex);
}
