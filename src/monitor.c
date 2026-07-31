/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbentes- <kbentes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 19:45:03 by kbentes-          #+#    #+#             */
/*   Updated: 2026/07/31 19:45:04 by kbentes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	all_compiled(t_program *program)
{
	int	i;
	int	n;
	int	required;

	i = 0;
	n = program->config.number_of_coders;
	required = program->config.number_of_compiles_required;
	while (i < n)
	{
		if (program->coders[i].compiles_done < required)
			return (0);
		i++;
	}
	return (1);
}

void	*monitor_routine(void *arg)
{
	t_program	*program;

	program = (t_program *)arg;
	while (!is_simulation_stopped(program))
	{
		if (all_compiled(program))
			stop_simulation(program);
		smart_sleep(1);
	}
	return (NULL);
}
