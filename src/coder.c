/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbentes- <kbentes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 22:19:47 by kbentes-          #+#    #+#             */
/*   Updated: 2026/07/30 22:17:37 by kbentes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	do_compile(t_coder *coder)
{
	acquire_dongles(coder);
	log_event(coder->program, coder->id, STATE_COMPILING);
	smart_sleep(coder->program->config.time_to_compile);
	release_dongles(coder);
	coder->compiles_done++;
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
	int		required;

	coder = (t_coder *)arg;
	required = coder->program->config.number_of_compiles_required;
	while (coder->compiles_done < required)
	{
		do_compile(coder);
		do_debug(coder);
		do_refactor(coder);
	}
	return (NULL);
}
