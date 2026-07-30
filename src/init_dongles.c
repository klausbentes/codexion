/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dongles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbentes- <kbentes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 04:24:37 by kbentes-          #+#    #+#             */
/*   Updated: 2026/07/29 22:45:17 by kbentes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	set_dongle(t_dongle *dongle, int id)
{
	dongle->id = id;
	if (pthread_mutex_init(&dongle->mutex, NULL) != 0)
		return (-1);
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
		if (set_dongle(&program->dongles[i], i) == -1)
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
