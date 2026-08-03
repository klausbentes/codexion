/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_remove.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbentes- <kbentes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 19:17:58 by kbentes-          #+#    #+#             */
/*   Updated: 2026/08/03 19:17:59 by kbentes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static int	find_index(t_heap *heap, int coder_id)
{
	int	i;

	i = 0;
	while (i < heap->size)
	{
		if (heap->items[i].coder_id == coder_id)
			return (i);
		i++;
	}
	return (-1);
}

void	heap_remove_id(t_heap *heap, int coder_id)
{
	int	index;

	index = find_index(heap, coder_id);
	if (index == -1)
		return ;
	heap->size--;
	heap->items[index] = heap->items[heap->size];
	if (index < heap->size)
	{
		sift_down(heap, index);
		sift_up(heap, index);
	}
}
