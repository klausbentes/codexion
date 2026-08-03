/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_pop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbentes- <kbentes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 18:36:47 by kbentes-          #+#    #+#             */
/*   Updated: 2026/08/03 18:36:48 by kbentes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static void	sift_down(t_heap *heap, int index)
{
	int	left;
	int	right;
	int	smallest;

	smallest = index;
	left = index * 2 + 1;
	right = index * 2 + 2;
	if (left < heap->size && request_less(&heap->items[left],
			&heap->items[smallest]))
		smallest = left;
	if (right < heap->size && request_less(&heap->items[right],
			&heap->items[smallest]))
		smallest = right;
	if (smallest != index)
	{
		swap_requests(&heap->items[index], &heap->items[smallest]);
		sift_down(heap, smallest);
	}
}

t_request	heap_pop(t_heap *heap)
{
	t_request	top;

	top = heap->items[0];
	heap->size--;
	heap->items[0] = heap->items[heap->size];
	if (heap->size > 0)
		sift_down(heap, 0);
	return (top);
}

int	heap_peek_id(t_heap *heap)
{
	if (heap->size == 0)
		return (-1);
	return (heap->items[0].coder_id);
}
