/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_coders.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbentes- <kbentes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 04:25:16 by kbentes-          #+#    #+#             */
/*   Updated: 2026/07/31 21:40:48 by kbentes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	set_coder(t_program *program, t_coder *coder, int index)
{
	int	n;

	n = program->config.number_of_coders;
	coder->id = index + 1;
	coder->compiles_done = 0;
	coder->program = program;
	coder->left_dongle = &program->dongles[index];
	coder->right_dongle = &program->dongles[(index + 1) % n];
	coder->last_compile_start = program->start_time;
	if (pthread_mutex_init(&coder->activity_mutex, NULL) != 0)
		return (-1);
	return (0);
}

int	init_coders(t_program *program)
{
	int	i;
	int	n;

	n = program->config.number_of_coders;
	program->coders = malloc(sizeof(t_coder) * n);
	if (!program->coders)
		return (-1);
	i = 0;
	while (i < n)
	{
		if (set_coder(program, &program->coders[i], i) == -1)
		{
			destroy_coders(program, i);
			free(program->coders);
			program->coders = NULL;
			return (-1);
		}
		i++;
	}
	return (0);
}
