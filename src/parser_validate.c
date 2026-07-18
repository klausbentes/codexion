/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbentes- <kbentes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 02:52:22 by kbentes-          #+#    #+#             */
/*   Updated: 2026/07/18 03:59:58 by kbentes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	check_scheduler(const char *str)
{
	if (strcmp(str, "fifo") == 0)
		return (FIFO_SCHED);
	if (strcmp(str, "edf") == 0)
		return (EDF_SCHED);
	print_error("scheduler must be exactly 'fifo' or 'edf'");
	return (-1);
}

int	parse_positive(const char *str, long *out)
{
	int	err;

	if (!is_all_digits(str))
	{
		print_error("argument must contain only digits");
		return (-1);
	}
	*out = str_to_long(str, &err);
	if (err || *out <= 0)
	{
		print_error("argument must be a positive number in range");
		return (-1);
	}
	return (0);
}
