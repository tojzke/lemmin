/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbg_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzboncak <dzboncak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 20:44:55 by dzboncak          #+#    #+#             */
/*   Updated: 2019/08/02 19:41:45 by dzboncak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_graph.h"

void				print_steps(t_lem *lem)
{
	t_list_of_steps *step;
	int				i;

	step = lem->steps;
	while (step != NULL)
	{
		i = 0;
		while (step->step[i] != NULL)
		{
			ft_printf(" %s ", step->step[i]);
			i++;
		}
		ft_putchar('\n');
		step = step->next;
	}
}

void				print_ants(t_lem *lem)
{
	t_list_of_ants	*ant;

	ant = lem->ants;
	while (ant != NULL)
	{
		ft_printf("Ant\n\tid:%d, cur_pos:%s, next_pos:%s\n", ant->id,
		ant->pos->name,
		ant->next_pos->name);
		ant = ant->next;
	}
}
