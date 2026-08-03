/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_dongles_pair.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbentes- <kbentes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 19:08:20 by kbentes-          #+#    #+#             */
/*   Updated: 2026/08/03 19:18:58 by kbentes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	acquire_pair(t_dongle *first, t_dongle *second, t_coder *coder)
{
	long long	key;
	long		cooldown;

	key = get_schedule_key(coder);
	cooldown = coder->program->config.dongle_cooldown;
	if (dongle_acquire(first, coder, key, cooldown) == -1)
		return (-1);
	log_event(coder->program, coder->id, STATE_TAKEN_DONGLE);
	if (dongle_acquire(second, coder, key, cooldown) == -1)
	{
		dongle_release(first);
		return (-1);
	}
	log_event(coder->program, coder->id, STATE_TAKEN_DONGLE);
	return (0);
}

void	release_pair(t_dongle *first, t_dongle *second)
{
	dongle_release(second);
	dongle_release(first);
}
