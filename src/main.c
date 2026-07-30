/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbentes- <kbentes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 02:58:58 by kbentes-          #+#    #+#             */
/*   Updated: 2026/07/29 22:24:41 by kbentes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	print_program_info(t_program *program)
{
	printf("Program initialized with %d coders and %d dongles\n",
		program->config.number_of_coders, program->config.number_of_coders);
}

int	main(int argc, char **argv)
{
	t_config	config;
	t_program	program;

	if (parse_args(argc, argv, &config) == -1)
	{
		print_usage();
		return (1);
	}
	if (init_program(&program, &config) == -1)
	{
		print_error("failed to initialize program");
		return (1);
	}
	print_program_info(&program);
	if (create_threads(&program) == -1)
	{
		print_error("failed to create threads");
		destroy_program(&program);
		return (1);
	}
	if (join_threads(&program) == -1)
	{
		print_error("failed to join threads");
		destroy_program(&program);
		return (1);
	}
	destroy_program(&program);
	return (0);
}
