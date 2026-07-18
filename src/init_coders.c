/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_coders.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbentes- <kbentes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 04:25:16 by kbentes-          #+#    #+#             */
/*   Updated: 2026/07/18 05:30:25 by kbentes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	set_coder(t_program *program, t_coder *coder, int index)
{
	int	n;

	n = program->config.number_of_coders;
	coder->id = index + 1;
	coder->compiles_done = 0;
	coder->program = program;
	coder->left_dongle = &program->dongles[index];
	coder->right_dongle = &program->dongles[(index + 1) % n];
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
		set_coder(program, &program->coders[i], i);
		i++;
	}
	return (0);
}