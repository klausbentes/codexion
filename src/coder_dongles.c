/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_dongles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbentes- <kbentes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 22:17:21 by kbentes-          #+#    #+#             */
/*   Updated: 2026/07/30 22:17:23 by kbentes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	acquire_dongles(t_coder *coder)
{
	pthread_mutex_lock(&coder->left_dongle->mutex);
	log_event(coder->program, coder->id, STATE_TAKEN_DONGLE);
	pthread_mutex_lock(&coder->right_dongle->mutex);
	log_event(coder->program, coder->id, STATE_TAKEN_DONGLE);
}

void	release_dongles(t_coder *coder)
{
	pthread_mutex_unlock(&coder->right_dongle->mutex);
	pthread_mutex_unlock(&coder->left_dongle->mutex);
}
