/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbentes- <kbentes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 04:26:07 by kbentes-          #+#    #+#             */
/*   Updated: 2026/08/03 18:37:57 by kbentes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	destroy_dongles(t_program *program, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		heap_destroy(&program->dongles[i].queue);
		pthread_cond_destroy(&program->dongles[i].cond);
		pthread_mutex_destroy(&program->dongles[i].mutex);
		i++;
	}
}

void	destroy_coders(t_program *program, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&program->coders[i].activity_mutex);
		i++;
	}
}

void	destroy_program(t_program *program)
{
	pthread_mutex_destroy(&program->state_mutex);
	if (program->coders)
	{
		destroy_coders(program, program->config.number_of_coders);
		free(program->coders);
		program->coders = NULL;
	}
	if (program->dongles)
	{
		destroy_dongles(program, program->config.number_of_coders);
		free(program->dongles);
		program->dongles = NULL;
	}
}
