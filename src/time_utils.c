/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbentes- <kbentes-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 21:18:43 by kbentes-          #+#    #+#             */
/*   Updated: 2026/07/29 21:18:46 by kbentes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long long	get_elapsed_ms(long long start)
{
	return (get_time_ms() - start);
}

void	smart_sleep(long long ms)
{
	if (ms <= 0)
		return ;
	usleep(ms * 1000);
}
