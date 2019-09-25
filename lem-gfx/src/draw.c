/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzboncak <dzboncak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 17:01:21 by dzboncak          #+#    #+#             */
/*   Updated: 2019/09/03 17:24:35 by dzboncak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_graph.h"

static void			draw_room(t_visual *vis, int x, int y, t_node *room)
{
	SDL_Rect		rect;

	rect.x = x;
	rect.y = y;
	rect.h = ROOM_H;
	rect.w = ROOM_W;
	if (room == vis->lem_data->start)
		SDL_SetRenderDrawColor(vis->rend, 51, 153, 255, 255);
	else if (room == vis->lem_data->end)
		SDL_SetRenderDrawColor(vis->rend, 255, 0, 51, 255);
	else
		SDL_SetRenderDrawColor(vis->rend, 255, 255, 255, 255);
	SDL_RenderFillRect(vis->rend, &rect);
}

static void			draw_rooms(t_visual *vis)
{
	t_list_of_nodes	*cur;

	cur = vis->lem_data->nodes;
	while (cur != NULL)
	{
		cur->node->draw_x = cur->node->x * vis->scale;
		cur->node->draw_x += vis->x_off / 5;
		cur->node->draw_y = cur->node->y * vis->scale;
		cur->node->draw_y += vis->y_off / 5;
		draw_room(vis, cur->node->draw_x, cur->node->draw_y, cur->node);
		cur = cur->next;
	}
}

static void			draw_connections(t_visual *vis)
{
	t_list_of_nodes	*cur;
	t_list_of_nodes	*adj;

	cur = vis->lem_data->nodes;
	SDL_SetRenderDrawColor(vis->rend, 255, 255, 255, 255);
	while (cur != NULL)
	{
		adj = cur->node->links;
		while (adj != NULL)
		{
			SDL_RenderDrawLine(vis->rend,
			cur->node->draw_x + ROOM_W / 2, cur->node->draw_y + ROOM_H / 2,
			adj->node->draw_x + ROOM_W / 2, adj->node->draw_y + ROOM_W / 2);
			adj = adj->next;
		}
		cur = cur->next;
	}
}

void				draw_all(t_visual *vis)
{
	SDL_SetRenderDrawColor(vis->rend, 153, 153, 153, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(vis->rend);
	SDL_RenderCopy(vis->rend, vis->background, 0, 0);
	draw_connections(vis);
	draw_rooms(vis);
	draw_ants(vis);
	SDL_RenderPresent(vis->rend);
}
