/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbentes- <kbentes-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 21:56:33 by kbentes-          #+#    #+#             */
/*   Updated: 2026/07/29 21:56:34 by kbentes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static const char	*get_state_str(t_state state)
{
	if (state == STATE_TAKEN_DONGLE)
		return ("has taken a dongle");
	if (state == STATE_COMPILING)
		return ("is compiling");
	if (state == STATE_DEBUGGING)
		return ("is debugging");
	if (state == STATE_REFACTORING)
		return ("is refactoring");
	return ("burned out");
}

void	log_event(t_program *program, int coder_id, t_state state)
{
	long long	elapsed;

	elapsed = get_elapsed_ms(program->start_time);
	printf("%lld %d %s\n", elapsed, coder_id, get_state_str(state));
}
