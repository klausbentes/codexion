/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder_dongles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbentes- <kbentes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 22:17:21 by kbentes-          #+#    #+#             */
/*   Updated: 2026/08/03 19:21:38 by kbentes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	is_last_coder(t_coder *coder)
{
	return (coder->id == coder->program->config.number_of_coders);
}

static void	get_dongle_order(t_coder *coder, t_dongle **first,
		t_dongle **second)
{
	if (is_last_coder(coder))
	{
		*first = coder->right_dongle;
		*second = coder->left_dongle;
	}
	else
	{
		*first = coder->left_dongle;
		*second = coder->right_dongle;
	}
}

int	acquire_dongles(t_coder *coder)
{
	t_dongle	*first;
	t_dongle	*second;

	get_dongle_order(coder, &first, &second);
	return (acquire_pair(first, second, coder));
}

void	release_dongles(t_coder *coder)
{
	t_dongle	*first;
	t_dongle	*second;

	get_dongle_order(coder, &first, &second);
	release_pair(first, second);
}
