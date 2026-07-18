/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbentes- <kbentes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 04:00:25 by kbentes-          #+#    #+#             */
/*   Updated: 2026/07/18 04:00:29 by kbentes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	fill_config(char **argv, t_config *cfg)
{
	long	values[7];
	int		i;

	i = 0;
	while (i < 7)
	{
		if (parse_positive(argv[i + 1], &values[i]) == -1)
			return (-1);
		i++;
	}
	cfg->number_of_coders = (int)values[0];
	cfg->time_to_burnout = values[1];
	cfg->time_to_compile = values[2];
	cfg->time_to_debug = values[3];
	cfg->time_to_refactor = values[4];
	cfg->number_of_compiles_required = (int)values[5];
	cfg->dongle_cooldown = values[6];
	cfg->scheduler = check_scheduler(argv[8]);
	if (cfg->scheduler == -1)
		return (-1);
	return (0);
}

int	parse_args(int argc, char **argv, t_config *cfg)
{
	if (argc != 9)
	{
		print_error("wrong number of arguments");
		return (-1);
	}
	if (fill_config(argv, cfg) == -1)
		return (-1);
	return (0);
}
