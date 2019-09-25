/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzboncak <dzboncak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 16:49:33 by dzboncak          #+#    #+#             */
/*   Updated: 2019/07/11 18:19:27 by dzboncak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void					delete_path(t_list_of_nodes *path)
{
	t_list_of_nodes *start;

	start = path;
	if (path == NULL)
		return ;
	while ((path)->next != NULL)
	{
		while ((path)->next->next != NULL)
			path = (path)->next;
		free((path)->next);
		(path)->next = NULL;
		path = start;
	}
	free(path);
}

static t_list_of_paths	*create_list_of_paths(t_list_of_nodes *first_path)
{
	t_list_of_paths *list;

	list = ft_memalloc(sizeof(t_list_of_paths));
	list->path = first_path;
	list->next = NULL;
	return (list);
}

void					push_path(t_list_of_paths **list,
						t_list_of_nodes *path)
{
	t_list_of_paths *start;

	if (*list == NULL)
		*list = create_list_of_paths(path);
	else
	{
		start = *list;
		while ((*list)->next != NULL)
			*list = (*list)->next;
		(*list)->next = ft_memalloc(sizeof(t_list_of_paths));
		(*list)->next->path = path;
		(*list)->next->next = NULL;
		*list = start;
	}
}

int						path_len(t_list_of_nodes *list)
{
	int i;

	i = 0;
	while (list)
	{
		i++;
		list = list->next;
	}
	return (i - 1);
}
