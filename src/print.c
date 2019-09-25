/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzboncak <dzboncak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 16:48:27 by dzboncak          #+#    #+#             */
/*   Updated: 2019/08/04 17:15:38 by dzboncak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void	color_on(t_list_of_ants *ants)
{
	if (ants->ant_id % 6 == 0)
		ft_putstr(RED);
	else if (ants->ant_id % 6 == 1)
		ft_putstr(GREEN);
	else if (ants->ant_id % 6 == 2)
		ft_putstr(YELLOW);
	else if (ants->ant_id % 6 == 3)
		ft_putstr(BLUE);
	else if (ants->ant_id % 6 == 4)
		ft_putstr(PURPLE);
	else if (ants->ant_id % 6 == 5)
		ft_putstr(CYAN);
}

void		print_steps(t_list_of_ants *ants, t_lem *lem)
{
	while (ants)
	{
		if (lem->flag_color)
		{
			color_on(ants);
			if (ants->position->node->marked)
				ft_putstr(BG_RED);
		}
		ft_printf("L%d-%s", ants->ant_id,
			ants->position->node->name);
		if (lem->flag_color)
			ft_putstr(DEFAULT);
		ft_putchar(' ');
		ants = ants->next;
	}
	ft_putchar('\n');
}

static void	print_path(t_list_of_nodes *path)
{
	while (1)
	{
		if (path->node->marked)
			ft_putstr(BG_RED);
		ft_putstr(path->node->name);
		if (path->node->marked)
			ft_putstr(BG_DEFAULT);
		if (path->next == NULL)
			break ;
		else
			ft_putstr("->");
		path = path->next;
	}
	ft_putchar('\n');
}

void		print_paths(t_list_of_paths *list, t_lem *lem)
{
	int				count;
	t_list_of_paths	*start;

	count = 0;
	if (lem->flag_color)
		ft_putstr(RED);
	ft_putstr("\nUnique paths:\n");
	start = list;
	while (list)
	{
		if (lem->flag_color)
		{
			if (++count % 2 == 0)
				ft_putstr(BLUE);
			else
				ft_putstr(YELLOW);
		}
		print_path(list->path);
		list = list->next;
	}
	ft_putstr(DEFAULT);
	list = start;
}

void		print_total_steps(int total, t_lem *lem)
{
	if (lem->flag_color)
		ft_putstr(RED);
	ft_printf("\nTolal steps: %d\n", total);
	if (lem->flag_color)
		ft_putstr(DEFAULT);
}
