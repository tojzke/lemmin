/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzboncak <dzboncak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 17:08:08 by dzboncak          #+#    #+#             */
/*   Updated: 2019/07/15 16:38:19 by dzboncak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_graph.h"

int				node_in_path(t_list_of_nodes *path, t_node *node)
{
	while (path != NULL)
	{
		if (path->node == node)
			return (1);
		path = path->next;
	}
	return (0);
}

static t_node	*find_node(char *name, t_list_of_nodes *nodes)
{
	while (nodes)
	{
		if (ft_strequ(name, nodes->node->name))
			return (nodes->node);
		nodes = nodes->next;
	}
	return (NULL);
}

void			create_link(char *line, t_lem *lem)
{
	char	**params;
	t_node	*n1;
	t_node	*n2;

	params = ft_strsplit(line, '-');
	if (ft_char_count(' ', line) != 0 || ft_arrlen(params) != 2)
		error("Link definition example: room_1-room_2", lem);
	n1 = find_node(params[0], lem->nodes);
	n2 = find_node(params[1], lem->nodes);
	ft_arrclr(params);
	if (n1 == NULL || n2 == NULL)
		error("No such room to link", lem);
	if (n1 == n2)
		error("Self-loops are forbidden", lem);
	if (!node_in_path(n1->links, n2) && !node_in_path(n2->links, n1))
	{
		push_node(&n1->links, n2);
		push_node(&n2->links, n1);
	}
	else
		error("Link duplication is forbidden", lem);
}
