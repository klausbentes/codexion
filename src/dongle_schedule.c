/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_schedule.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbentes- <kbentes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 18:37:06 by kbentes-          #+#    #+#             */
/*   Updated: 2026/08/03 18:46:15 by kbentes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long long	get_schedule_key(t_coder *coder)
{
	if (coder->program->config.scheduler == FIFO_SCHED)
		return (get_time_ms());
	return (get_last_compile_start(coder)
		+ coder->program->config.time_to_burnout);
}

static int	is_ready(t_dongle *dongle, t_coder *coder, long cooldown)
{
	if (dongle->locked)
		return (0);
	if (heap_peek_id(&dongle->queue) != coder->id)
		return (0);
	if (cooldown_remaining_ms(dongle, cooldown) > 0)
		return (0);
	return (1);
}

static void	wait_turn(t_dongle *dongle, t_coder *coder, long cooldown)
{
	struct timespec	ts;
	long long		remaining;

	while (!is_ready(dongle, coder, cooldown))
	{
		remaining = cooldown_remaining_ms(dongle, cooldown);
		if (remaining > 0)
		{
			ms_to_timespec(get_time_ms() + remaining, &ts);
			pthread_cond_timedwait(&dongle->cond, &dongle->mutex, &ts);
		}
		else
			pthread_cond_wait(&dongle->cond, &dongle->mutex);
	}
}

void	dongle_acquire(t_dongle *dongle, t_coder *coder,
		long long key, long cooldown)
{
	t_request	req;

	pthread_mutex_lock(&dongle->mutex);
	req.coder_id = coder->id;
	req.key = key;
	req.seq = dongle->next_seq++;
	heap_push(&dongle->queue, req);
	wait_turn(dongle, coder, cooldown);
	heap_pop(&dongle->queue);
	dongle->locked = 1;
	pthread_mutex_unlock(&dongle->mutex);
}

void	dongle_release(t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->mutex);
	dongle->locked = 0;
	dongle->released_at = get_time_ms();
	pthread_cond_broadcast(&dongle->cond);
	pthread_mutex_unlock(&dongle->mutex);
}
