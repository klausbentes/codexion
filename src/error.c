/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbentes- <kbentes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 02:57:34 by kbentes-          #+#    #+#             */
/*   Updated: 2026/07/18 04:18:06 by kbentes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	print_usage(void)
{
	write(2, "Usage: ./codexion number_of_coders time_to_burnout ", 51);
	write(2, "time_to_compile time_to_debug time_to_refactor ", 47);
	write(2, "number_of_compiles_required dongle_cooldown scheduler\n", 54);
}

int	print_error(const char *msg)
{
	fprintf(stderr, "Error: %s\n", msg);
	return (-1);
}
