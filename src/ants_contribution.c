/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_contribution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzboncak <dzboncak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 16:50:53 by dzboncak          #+#    #+#             */
/*   Updated: 2019/07/11 18:19:29 by dzboncak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	step(t_list_of_ants *ants)
{
	t_list_of_ants *buf;

	buf = ants;
	while (buf)
	{
		buf->position = buf->position->next;
		buf = buf->next;
	}
}

static int	count_ways_sum(t_list_of_paths *start, t_list_of_paths *curr)
{
	int ways_sum;

	ways_sum = 0;
	while (start != curr)
	{
		ways_sum += path_len(curr->path) - path_len(start->path);
		start = start->next;
	}
	return (ways_sum);
}

static void	new_ants(t_list_of_ants **ants, t_list_of_paths *paths,
		int *ant_counter, t_lem *lem)
{
	t_list_of_paths	*start;

	start = paths;
	while (paths && lem->ants - *ant_counter != 0)
	{
		if (start->path->node == lem->start &&
			start->path->next->node == lem->end)
		{
			(*ant_counter)++;
			push_ant(ants, *ant_counter, paths->path);
		}
		else
		{
			if (lem->ants - *ant_counter > count_ways_sum(start, paths))
			{
				(*ant_counter)++;
				push_ant(ants, *ant_counter, paths->path);
			}
			paths = paths->next;
		}
	}
	paths = start;
}

static void	remove_finishers(t_list_of_ants **ants, t_lem *lem)
{
	t_list_of_ants *tmp;

	tmp = *ants;
	while (tmp)
	{
		if (tmp->position->node == lem->end)
			remove_ant(ants, tmp);
		tmp = tmp->next;
	}
}

void		ants_contribution(t_list_of_paths *paths, t_lem *lem)
{
	t_list_of_ants	*ants;
	int				ant_counter;
	int				total;

	ants = NULL;
	ant_counter = 0;
	total = 0;
	new_ants(&ants, paths, &ant_counter, lem);
	while (ants)
	{
		step(ants);
		print_steps(ants, lem);
		remove_finishers(&ants, lem);
		new_ants(&ants, paths, &ant_counter, lem);
		total++;
	}
	if (lem->flag_paths)
		print_paths(paths, lem);
	if (lem->flag_steps)
		print_total_steps(total, lem);
}
