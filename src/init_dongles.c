/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dongles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbentes- <kbentes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 04:24:37 by kbentes-          #+#    #+#             */
/*   Updated: 2026/08/03 18:46:54 by kbentes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	set_dongle(t_dongle *dongle, int id, int capacity)
{
	dongle->id = id;
	dongle->locked = 0;
	dongle->next_seq = 0;
	dongle->released_at = -1;
	if (pthread_mutex_init(&dongle->mutex, NULL) != 0)
		return (-1);
	if (pthread_cond_init(&dongle->cond, NULL) != 0)
	{
		pthread_mutex_destroy(&dongle->mutex);
		return (-1);
	}
	if (heap_init(&dongle->queue, capacity) != 0)
	{
		pthread_cond_destroy(&dongle->cond);
		pthread_mutex_destroy(&dongle->mutex);
		return (-1);
	}
	return (0);
}

int	init_dongles(t_program *program)
{
	int	i;
	int	n;

	n = program->config.number_of_coders;
	program->dongles = malloc(sizeof(t_dongle) * n);
	if (!program->dongles)
		return (-1);
	i = 0;
	while (i < n)
	{
		if (set_dongle(&program->dongles[i], i, n) == -1)
		{
			destroy_dongles(program, i);
			free(program->dongles);
			program->dongles = NULL;
			return (-1);
		}
		i++;
	}
	return (0);
}
