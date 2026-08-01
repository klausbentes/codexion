/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_activity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbentes- <kbentes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/31 21:40:22 by kbentes-          #+#    #+#             */
/*   Updated: 2026/07/31 21:40:24 by kbentes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	update_last_compile_start(t_coder *coder)
{
	pthread_mutex_lock(&coder->activity_mutex);
	coder->last_compile_start = get_time_ms();
	pthread_mutex_unlock(&coder->activity_mutex);
}

long long	get_last_compile_start(t_coder *coder)
{
	long long	value;

	pthread_mutex_lock(&coder->activity_mutex);
	value = coder->last_compile_start;
	pthread_mutex_unlock(&coder->activity_mutex);
	return (value);
}
