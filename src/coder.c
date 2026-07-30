/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coder.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbentes- <kbentes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 22:19:47 by kbentes-          #+#    #+#             */
/*   Updated: 2026/07/29 22:24:11 by kbentes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	*coder_routine(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	log_event(coder->program, coder->id, STATE_COMPILING);
	smart_sleep(coder->program->config.time_to_compile);
	log_event(coder->program, coder->id, STATE_DEBUGGING);
	return (NULL);
}
