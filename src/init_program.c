/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbentes- <kbentes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 04:25:45 by kbentes-          #+#    #+#             */
/*   Updated: 2026/07/29 21:54:32 by kbentes-         ###   ########.fr       */
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
	program->start_time = get_time_ms();
	if (init_dongles(program) == -1)
		return (-1);
	if (init_coders(program) == -1)
	{
		free(program->dongles);
		program->dongles = NULL;
		return (-1);
	}
	return (0);
}
