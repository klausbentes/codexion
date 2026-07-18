/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbentes- <kbentes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 04:26:07 by kbentes-          #+#    #+#             */
/*   Updated: 2026/07/18 04:26:11 by kbentes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	destroy_program(t_program *program)
{
	free(program->coders);
	program->coders = NULL;
	free(program->dongles);
	program->dongles = NULL;
}
