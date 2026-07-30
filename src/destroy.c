/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbentes- <kbentes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 04:26:07 by kbentes-          #+#    #+#             */
/*   Updated: 2026/07/29 22:45:27 by kbentes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	destroy_dongles(t_program *program, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_destroy(&program->dongles[i].mutex);
		i++;
	}
}

void	destroy_program(t_program *program)
{
	free(program->coders);
	program->coders = NULL;
	if (program->dongles)
	{
		destroy_dongles(program, program->config.number_of_coders);
		free(program->dongles);
		program->dongles = NULL;
	}
}