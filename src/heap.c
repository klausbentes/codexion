/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbentes- <kbentes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 18:36:32 by kbentes-          #+#    #+#             */
/*   Updated: 2026/08/03 18:36:34 by kbentes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	heap_init(t_heap *heap, int capacity)
{
	heap->items = malloc(sizeof(t_request) * capacity);
	if (!heap->items)
		return (-1);
	heap->size = 0;
	heap->capacity = capacity;
	return (0);
}

void	heap_destroy(t_heap *heap)
{
	free(heap->items);
	heap->items = NULL;
	heap->size = 0;
	heap->capacity = 0;
}

static void	sift_up(t_heap *heap, int index)
{
	int	parent;

	while (index > 0)
	{
		parent = (index - 1) / 2;
		if (!request_less(&heap->items[index], &heap->items[parent]))
			break ;
		swap_requests(&heap->items[parent], &heap->items[index]);
		index = parent;
	}
}

void	heap_push(t_heap *heap, t_request request)
{
	heap->items[heap->size] = request;
	sift_up(heap, heap->size);
	heap->size++;
}
