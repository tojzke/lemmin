/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pathes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzboncak <dzboncak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 17:15:12 by dzboncak          #+#    #+#             */
/*   Updated: 2019/08/04 17:15:17 by dzboncak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		remove_node(t_list_of_nodes **list, t_node *node)
{
	t_list_of_nodes *tmp;
	t_list_of_nodes *start;

	tmp = NULL;
	if ((*list)->node == node)
	{
		tmp = *list;
		*list = (*list)->next;
	}
	else
	{
		start = *list;
		while ((*list)->next)
		{
			if ((*list)->next->node == node)
			{
				tmp = (*list)->next;
				(*list)->next = (*list)->next->next;
				break ;
			}
			*list = (*list)->next;
		}
		*list = start;
	}
	free(tmp);
}

static void	start_to_end_handle(t_lem *lem, t_list_of_paths **paths_1,
		t_list_of_paths **paths_2)
{
	t_list_of_nodes *path;

	if (node_in_path(lem->start->links, lem->end))
	{
		path = NULL;
		push_node(&path, lem->start);
		push_node(&path, lem->end);
		push_path(paths_1, path);
		push_path(paths_2, path);
		remove_node(&lem->start->links, lem->end);
		remove_node(&lem->end->links, lem->start);
	}
}

static void	reset_used_nodes(t_list_of_nodes *list, t_lem *lem)
{
	reset_nodes_in_queue(list, lem);
	while (list)
	{
		list->node->bfs_used = 0;
		list = list->next;
	}
}

void		get_paths(t_list_of_paths **paths_1, t_list_of_paths **paths_2,
			t_lem *lem)
{
	t_list_of_nodes *path;

	start_to_end_handle(lem, paths_1, paths_2);
	while ((path = bfs(lem, BFS_ORIGINAL)))
		push_path(paths_1, path);
	reset_used_nodes(lem->nodes, lem);
	sort_nodes_by_amount_of_links(lem->nodes);
	while ((path = bfs(lem, BFS_SORTED)))
		push_path(paths_2, path);
	sort_paths_by_len(*paths_2);
	if (!*paths_1 && !*paths_2)
		error("Not enough data to process", lem);
}
