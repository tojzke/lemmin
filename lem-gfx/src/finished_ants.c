/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finished_ants.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzboncak <dzboncak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 18:57:43 by dzboncak          #+#    #+#             */
/*   Updated: 2019/08/02 19:40:05 by dzboncak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_graph.h"

/*
** If ant reached next node update its pos and next_pos
*/

void		update_ant_pos(t_list_of_ants *ant,
t_list_of_steps *cur, t_list_of_nodes *room)
{
	int		i;

	if (cur->next != NULL)
	{
		i = 0;
		cur = cur->next;
		ant->pos = ant->next_pos;
		while (cur->step[i] != NULL)
		{
			if (ant->id == get_id(cur->step[i]))
			{
				ant->next_pos = get_next_pos(cur->step[i], room);
				return ;
			}
			i++;
		}
		ant->next_pos = NULL;
	}
}

/*
** Checks if every ant is finished his step == step fully finished
*/

int			step_done(t_list_of_ants *ant)
{
	while (ant != NULL)
	{
		if (!ant->finished)
			return (0);
		ant = ant->next;
	}
	return (1);
}

/*
** Checks if ant has reached its next_pos
*/

int			is_finished(t_list_of_ants *ant,
					t_list_of_steps *cur, t_list_of_nodes *room)
{
	int		x_diff;
	int		y_diff;
	int		diff;

	if (ant->finished == 1)
		return (1);
	x_diff = (ant->next_pos->draw_x + ROOM_W / 2) - (ant->x_pos + LEM_W / 2);
	x_diff *= x_diff;
	y_diff = (ant->next_pos->draw_y + ROOM_H / 2) - (ant->y_pos + LEM_H / 2);
	y_diff *= y_diff;
	diff = sqrt(x_diff + y_diff);
	if ((int)sqrt(x_diff + y_diff) < (2))
	{
		update_ant_pos(ant, cur, room);
		return (ant->finished = 1);
	}
	return (ant->finished = 0);
}

/*
** Step is done
** set every ant as unfinished his step
*/

void		set_unfinished(t_list_of_ants *ant)
{
	while (ant != NULL)
	{
		ant->finished = 0;
		ant = ant->next;
	}
}
