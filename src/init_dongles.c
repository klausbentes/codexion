/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dongles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbentes- <kbentes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 04:24:37 by kbentes-          #+#    #+#             */
/*   Updated: 2026/07/18 05:30:08 by kbentes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	set_dongle(t_dongle *dongle, int id)
{
	dongle->id = id;
}

int	init_dongles(t_program *program)
{
	int	i;
	int	n;

	n = program->config.number_of_coders;
	program->dongles = malloc(sizeof(t_dongle) * n);
	if (!program->dongles)
		return (-1);
	i = 0;
	while (i < n)
	{
		set_dongle(&program->dongles[i], i);
		i++;
	}
	return (0);
}
