/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_cooldown.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbentes- <kbentes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 18:45:18 by kbentes-          #+#    #+#             */
/*   Updated: 2026/08/03 18:45:20 by kbentes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

long long	cooldown_remaining_ms(t_dongle *dongle, long cooldown)
{
	long long	elapsed;

	if (dongle->released_at < 0)
		return (0);
	elapsed = get_time_ms() - dongle->released_at;
	if (elapsed >= cooldown)
		return (0);
	return (cooldown - elapsed);
}
