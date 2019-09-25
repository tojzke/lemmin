/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzboncak <dzboncak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 19:06:44 by dzboncak          #+#    #+#             */
/*   Updated: 2019/08/02 19:50:54 by dzboncak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_graph.h"

/*
** Create node with ant info
*/

t_list_of_ants		*create_ant(t_lem *lem, char *ant_step)
{
	t_list_of_ants	*ant;
	t_list_of_ants	*tmp;

	ant = ft_memalloc(sizeof(t_list_of_ants));
	ant->id = get_id(ant_step);
	ant->pos = lem->start;
	ant->next_pos = get_next_pos(ant_step, lem->nodes);
	ant->x_pos = ant->pos->draw_x + ROOM_W / 2 - LEM_W / 2;
	ant->y_pos = ant->pos->draw_y + ROOM_H / 2 - LEM_H / 2;
	ant->finished = 0;
	ant->next = NULL;
	if (lem->ants == NULL)
		return (lem->ants = ant);
	tmp = lem->ants;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	return (tmp->next = ant);
}

/*
** Find ant in ant list
** if can't find ant with this id - create new ant
*/

t_list_of_ants		*find_ant(t_lem *lem, char *ant_step)
{
	t_list_of_ants	*ant;

	ant = lem->ants;
	while (ant != NULL)
	{
		if (ant->id == get_id(ant_step))
			return (ant);
		ant = ant->next;
	}
	if (get_next_pos(ant_step, lem->nodes) == lem->end)
		return (NULL);
	return (create_ant(lem, ant_step));
}

/*
** If ant reached end - remove him from the list
*/

void				remove_ant(t_list_of_ants **ants, t_list_of_ants *ant)
{
	t_list_of_ants	*tmp;
	t_list_of_ants	*start;

	tmp = NULL;
	if (*ants == ant)
	{
		tmp = *ants;
		*ants = (*ants)->next;
	}
	else
	{
		start = *ants;
		while (start->next)
		{
			if (start->next == ant)
			{
				tmp = start->next;
				start->next = start->next->next;
				break ;
			}
			start = start->next;
		}
	}
	free(tmp);
}

/*
** Update positions of each ant and draw them
*/

void				draw_ants(t_visual *vis)
{
	t_list_of_ants	*ant;
	t_list_of_steps	*cr_step;
	int				i;

	if (vis->lem_data->cur_step == NULL)
		return ;
	cr_step = vis->lem_data->cur_step;
	i = 0;
	while (cr_step->step[i] != NULL)
	{
		if (!(ant = find_ant(vis->lem_data, cr_step->step[i])) ||
		!move_ant(ant, cr_step, vis))
		{
			i++;
			continue ;
		}
		i++;
	}
	if (step_done(vis->lem_data->ants))
	{
		vis->lem_data->cur_step = cr_step->next;
		set_unfinished(vis->lem_data->ants);
	}
}
