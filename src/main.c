/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbentes- <kbentes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 02:58:58 by kbentes-          #+#    #+#             */
/*   Updated: 2026/07/18 04:01:44 by kbentes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	print_config(t_config *cfg)
{
	printf("number_of_coders: %d\n", cfg->number_of_coders);
	printf("time_to_burnout: %ld\n", cfg->time_to_burnout);
	printf("time_to_compile: %ld\n", cfg->time_to_compile);
	printf("time_to_debug: %ld\n", cfg->time_to_debug);
	printf("time_to_refactor: %ld\n", cfg->time_to_refactor);
	printf("number_of_compiles_required: %d\n",
		cfg->number_of_compiles_required);
	printf("dongle_cooldown: %ld\n", cfg->dongle_cooldown);
	if (cfg->scheduler == FIFO_SCHED)
		printf("scheduler: fifo\n");
	else
		printf("scheduler: edf\n");
}

int	main(int argc, char **argv)
{
	t_config	cfg;

	if (parse_args(argc, argv, &cfg) == -1)
	{
		print_usage();
		return (1);
	}
	print_config(&cfg);
	return (0);
}
