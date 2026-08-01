/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbentes- <kbentes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 19:45:03 by kbentes-          #+#    #+#             */
/*   Updated: 2026/07/31 21:41:59 by kbentes-         ###   ########.fr       */
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

static int	coder_has_burned_out(t_coder *coder, long time_to_burnout)
{
	long long	elapsed;

	elapsed = get_elapsed_ms(get_last_compile_start(coder));
	return (elapsed > time_to_burnout);
}

static int	check_burnout(t_program *program)
{
	int	i;
	int	n;

	i = 0;
	n = program->config.number_of_coders;
	while (i < n)
	{
		if (coder_has_burned_out(&program->coders[i],
				program->config.time_to_burnout))
		{
			log_event(program, program->coders[i].id, STATE_BURNED_OUT);
			stop_simulation(program);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_program	*program;

	program = (t_program *)arg;
	while (!is_simulation_stopped(program))
	{
		if (check_burnout(program))
			break ;
		if (all_compiled(program))
			stop_simulation(program);
		smart_sleep(1);
	}
	return (NULL);
}
