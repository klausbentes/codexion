/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbentes- <kbentes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 22:19:47 by kbentes-          #+#    #+#             */
/*   Updated: 2026/08/03 19:19:15 by kbentes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	do_compile(t_coder *coder)
{
	if (acquire_dongles(coder) == -1)
		return (0);
	update_last_compile_start(coder);
	log_event(coder->program, coder->id, STATE_COMPILING);
	smart_sleep(coder->program->config.time_to_compile);
	release_dongles(coder);
	coder->compiles_done++;
	return (1);
}

static void	do_debug(t_coder *coder)
{
	log_event(coder->program, coder->id, STATE_DEBUGGING);
	smart_sleep(coder->program->config.time_to_debug);
}

static void	do_refactor(t_coder *coder)
{
	log_event(coder->program, coder->id, STATE_REFACTORING);
	smart_sleep(coder->program->config.time_to_refactor);
}

void	*coder_routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	while (!is_simulation_stopped(coder->program))
	{
		if (!do_compile(coder))
			break ;
		do_debug(coder);
		do_refactor(coder);
	}
	return (NULL);
}
