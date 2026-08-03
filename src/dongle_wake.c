/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_wake.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbentes- <kbentes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 19:18:21 by kbentes-          #+#    #+#             */
/*   Updated: 2026/08/03 19:18:22 by kbentes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	wake_all_dongles(t_program *program)
{
	int	i;
	int	n;

	i = 0;
	n = program->config.number_of_coders;
	while (i < n)
	{
		pthread_mutex_lock(&program->dongles[i].mutex);
		pthread_cond_broadcast(&program->dongles[i].cond);
		pthread_mutex_unlock(&program->dongles[i].mutex);
		i++;
	}
}
