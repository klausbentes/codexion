/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbentes- <kbentes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 22:24:25 by kbentes-          #+#    #+#             */
/*   Updated: 2026/07/29 22:24:28 by kbentes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	create_threads(t_program *program)
{
	int	i;
	int	n;

	n = program->config.number_of_coders;
	i = 0;
	while (i < n)
	{
		if (pthread_create(&program->coders[i].thread, NULL,
				coder_routine, &program->coders[i]) != 0)
			return (-1);
		i++;
	}
	return (0);
}

int	join_threads(t_program *program)
{
	int	i;
	int	n;

	n = program->config.number_of_coders;
	i = 0;
	while (i < n)
	{
		if (pthread_join(program->coders[i].thread, NULL) != 0)
			return (-1);
		i++;
	}
	return (0);
}
