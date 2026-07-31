/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbentes- <kbentes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 22:19:47 by kbentes-          #+#    #+#             */
/*   Updated: 2026/07/30 21:18:09 by kbentes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	acquire_dongles(t_coder *coder)
{
	pthread_mutex_lock(&coder->left_dongle->mutex);
	log_event(coder->program, coder->id, STATE_TAKEN_DONGLE);
	pthread_mutex_lock(&coder->right_dongle->mutex);
	log_event(coder->program, coder->id, STATE_TAKEN_DONGLE);
}

static void	release_dongles(t_coder *coder)
{
	pthread_mutex_unlock(&coder->right_dongle->mutex);
	pthread_mutex_unlock(&coder->left_dongle->mutex);
}

static void	do_compile(t_coder *coder)
{
	log_event(coder->program, coder->id, STATE_COMPILING);
	smart_sleep(coder->program->config.time_to_compile);
}

void	*coder_routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	acquire_dongles(coder);
	do_compile(coder);
	release_dongles(coder);
	return (NULL);
}
