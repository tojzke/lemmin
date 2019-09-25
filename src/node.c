/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzboncak <dzboncak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 16:49:42 by dzboncak          #+#    #+#             */
/*   Updated: 2019/07/09 16:49:45 by dzboncak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_list_of_nodes	*create_list_of_nodes(t_node *first_node)
{
	t_list_of_nodes *list;

	list = ft_memalloc(sizeof(t_list_of_nodes));
	list->node = first_node;
	list->next = NULL;
	return (list);
}

int				push_node(t_list_of_nodes **list, t_node *node)
{
	t_list_of_nodes	*start;
	t_list_of_nodes	*tmp;
	int				unique;

	tmp = *list;
	unique = 1;
	while (tmp)
	{
		if (ft_strequ(tmp->node->name, node->name))
			unique = 0;
		tmp = tmp->next;
	}
	if (*list == NULL)
		*list = create_list_of_nodes(node);
	else
	{
		start = *list;
		while (start->next != NULL)
			start = start->next;
		start->next = ft_memalloc(sizeof(t_list_of_nodes));
		start->next->node = node;
		start->next->next = NULL;
	}
	return (unique);
}

t_node			*pop_node(t_list_of_nodes **list)
{
	t_node			*res;
	t_list_of_nodes	*erase;

	if (*list == NULL)
		return (NULL);
	res = (*list)->node;
	erase = *list;
	*list = (*list)->next;
	free(erase);
	erase = NULL;
	return (res);
}

static void		handle_errors(char *line, char **params, t_lem *lem)
{
	char	*itoa1;
	char	*itoa2;

	if (ft_arrlen(params) != 3 || ft_char_count(' ', line) != 2)
		error("Room definition example: 'name x y'", lem);
	if (params[0][0] == 'L')
		error("Room's name must not start with the character 'L'", lem);
	if (params[0][0] == '#')
		error("Room's name must not start with the character '#'", lem);
	if (ft_char_count('-', params[0]) != 0)
		error("Room's name must not contain the character '-'", lem);
	itoa1 = ft_itoa(ft_atoi(params[1]));
	itoa2 = ft_itoa(ft_atoi(params[2]));
	if (!ft_strequ(itoa1, params[1]) || !ft_strequ(itoa2, params[2]))
		error("Room's coordinates must be integers", lem);
	ft_strdel(&itoa1);
	ft_strdel(&itoa2);
}

t_node			*create_node(char *line, t_lem *lem)
{
	char	**params;
	t_node	*node;

	params = ft_strsplit(line, ' ');
	handle_errors(line, params, lem);
	node = ft_memalloc(sizeof(t_node));
	node->name = ft_strdup(params[0]);
	node->bfs_used = 0;
	node->bfs_in_queue = 0;
	node->marked = 0;
	node->x = ft_atoi(params[1]);
	node->y = ft_atoi(params[2]);
	node->links = NULL;
	ft_arrclr(params);
	return (node);
}
