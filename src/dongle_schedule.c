/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_schedule.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbentes- <kbentes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 18:37:06 by kbentes-          #+#    #+#             */
/*   Updated: 2026/08/03 18:37:11 by kbentes-         ###   ########.fr       */
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

void	dongle_acquire(t_dongle *dongle, t_coder *coder, long long key)
{
	t_request	req;

	pthread_mutex_lock(&dongle->mutex);
	req.coder_id = coder->id;
	req.key = key;
	req.seq = dongle->next_seq++;
	heap_push(&dongle->queue, req);
	while (dongle->locked || heap_peek_id(&dongle->queue) != coder->id)
		pthread_cond_wait(&dongle->cond, &dongle->mutex);
	heap_pop(&dongle->queue);
	dongle->locked = 1;
	pthread_mutex_unlock(&dongle->mutex);
}

void	dongle_release(t_dongle *dongle)
{
	pthread_mutex_lock(&dongle->mutex);
	dongle->locked = 0;
	pthread_cond_broadcast(&dongle->cond);
	pthread_mutex_unlock(&dongle->mutex);
}
