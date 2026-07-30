/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbentes- <kbentes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 02:58:58 by kbentes-          #+#    #+#             */
/*   Updated: 2026/07/29 22:00:38 by kbentes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	print_program_info(t_program *program)
{
	printf("Program initialized with %d coders and %d dongles\n",
		program->config.number_of_coders, program->config.number_of_coders);
}

static void	test_logger(t_program *program)
{
	log_event(program, 1, STATE_TAKEN_DONGLE);
	log_event(program, 1, STATE_TAKEN_DONGLE);
	log_event(program, 1, STATE_COMPILING);
	smart_sleep(200);
	log_event(program, 1, STATE_DEBUGGING);
	smart_sleep(201);
	log_event(program, 1, STATE_REFACTORING);
	smart_sleep(100);
	log_event(program, 2, STATE_BURNED_OUT);
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
	test_logger(&program);
	destroy_program(&program);
	return (0);
}
