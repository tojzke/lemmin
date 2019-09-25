/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving_ants.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzboncak <dzboncak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 17:31:00 by dzboncak          #+#    #+#             */
/*   Updated: 2019/08/02 19:45:54 by dzboncak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_graph.h"

void	calc_speed(t_list_of_ants *ant, float *x_vel, float *y_vel)
{
	int		x_diff;
	int		y_diff;

	x_diff = (int)abs(ant->next_pos->draw_x - ant->pos->draw_x);
	y_diff = (int)abs(ant->next_pos->draw_y - ant->pos->draw_y);
	if (x_diff > y_diff)
	{
		*y_vel = ANT_SPEED / 60.0;
		if (y_diff != 0)
			*x_vel = ANT_SPEED * ((float)x_diff / (float)y_diff) / 60;
		else
			*x_vel = ANT_SPEED * 2 / 60.0;
	}
	else
	{
		*x_vel = ANT_SPEED / 60.0;
		if (x_diff != 0)
			*y_vel = ANT_SPEED * ((float)y_diff / (float)x_diff) / 60;
		else
			*y_vel = ANT_SPEED * 2 / 60.0;
	}
}

/*
** Slightly move ant each frame
*/

void	update_x_y(t_list_of_ants *ant, SDL_Rect *rect)
{
	float	x_vel;
	float	y_vel;

	if (!ant->finished)
	{
		calc_speed(ant, &x_vel, &y_vel);
		if ((ant->pos->draw_x + ROOM_W / 2) <
		(ant->next_pos->draw_x + ROOM_W / 2))
			ant->x_pos += x_vel;
		else if ((ant->pos->draw_x + ROOM_W / 2) >
		(ant->next_pos->draw_x + ROOM_W / 2))
			ant->x_pos -= x_vel;
		if ((ant->pos->draw_y + ROOM_H / 2) <
		(ant->next_pos->draw_y + ROOM_H / 2))
			ant->y_pos += y_vel;
		else if ((ant->pos->draw_y + ROOM_H / 2) >
		(ant->next_pos->draw_y + ROOM_H / 2))
			ant->y_pos -= y_vel;
	}
	rect->h = LEM_H;
	rect->w = LEM_W;
	rect->x = (int)ant->x_pos;
	rect->y = (int)ant->y_pos;
}

int		move_ant(t_list_of_ants *ant, t_list_of_steps *cr_step,
t_visual *vis)
{
	SDL_Rect		d_rect;

	update_x_y(ant, &d_rect);
	if (is_finished(ant, cr_step, vis->lem_data->nodes) &&
		ant->pos == vis->lem_data->end)
	{
		remove_ant(&vis->lem_data->ants, ant);
		return (0);
	}
	SDL_RenderCopy(vis->rend, vis->ant, NULL, &d_rect);
	return (1);
}

/*
** Get and id in current step
*/

int		get_id(char *str)
{
	str = ft_strchr(str, 'L') + 1;
	return (ft_atoi(str));
}

/*
** Get position where ant is moving towards
*/

t_node	*get_next_pos(char *str, t_list_of_nodes *room)
{
	str = ft_strchr(str, '-') + 1;
	while (room != NULL)
	{
		if (ft_strequ(str, room->node->name))
			return (room->node);
		room = room->next;
	}
	return (NULL);
}
