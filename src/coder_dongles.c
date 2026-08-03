/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_dongles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbentes- <kbentes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 22:17:21 by kbentes-          #+#    #+#             */
/*   Updated: 2026/08/03 18:37:25 by kbentes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	is_last_coder(t_coder *coder)
{
	return (coder->id == coder->program->config.number_of_coders);
}

static void	acquire_in_order(t_dongle *first, t_dongle *second, t_coder *coder)
{
	long long	key;

	key = get_schedule_key(coder);
	dongle_acquire(first, coder, key);
	log_event(coder->program, coder->id, STATE_TAKEN_DONGLE);
	dongle_acquire(second, coder, key);
	log_event(coder->program, coder->id, STATE_TAKEN_DONGLE);
}

static void	release_in_order(t_dongle *first, t_dongle *second)
{
	dongle_release(second);
	dongle_release(first);
}

void	acquire_dongles(t_coder *coder)
{
	if (is_last_coder(coder))
		acquire_in_order(coder->right_dongle, coder->left_dongle, coder);
	else
		acquire_in_order(coder->left_dongle, coder->right_dongle, coder);
}

void	release_dongles(t_coder *coder)
{
	if (is_last_coder(coder))
		release_in_order(coder->right_dongle, coder->left_dongle);
	else
		release_in_order(coder->left_dongle, coder->right_dongle);
}
