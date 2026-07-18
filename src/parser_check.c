/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbentes- <kbentes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 02:50:08 by kbentes-          #+#    #+#             */
/*   Updated: 2026/07/18 03:57:59 by kbentes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	is_all_digits(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

long	str_to_long(const char *str, int *err)
{
	long	result;
	int		i;

	result = 0;
	i = 0;
	*err = 0;
	while (str[i])
	{
		if (result > (LONG_MAX - (str[i] - '0')) / 10)
		{
			*err = 1;
			return (0);
		}
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result);
}
