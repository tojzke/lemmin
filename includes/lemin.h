/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzboncak <dzboncak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 16:38:10 by dzboncak          #+#    #+#             */
/*   Updated: 2019/08/04 17:15:57 by dzboncak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# include "libft.h"

# define MAP_ROOMS_MODE			0
# define MAP_LINKS_MODE			1
# define MAP_ANTS_MODE			2
# define GNL_READ_MODE			0
# define GNL_RETURN_COUNT_MODE	1
# define BFS_ORIGINAL			0
# define BFS_SORTED				1
# define DEFAULT				"\033[0m"
# define RED					"\033[1;31m"
# define GREEN					"\033[1;32m"
# define YELLOW					"\033[1;33m"
# define BLUE					"\033[1;34m"
# define PURPLE					"\033[1;35m"
# define CYAN					"\033[1;36m"
# define BG_RED					"\033[41m"
# define BG_DEFAULT				"\033[40m"

/*
**	name - room's name
**	links - list of pointers to linked rooms
**	x - coordinate x
**	y - coordinate y
**	bfs_prev - previous room for forming path
**	bfs_in_queue - equals 1 if queue contains this node
**	marked - equals 1 if command ##mark modified this node
*/

typedef struct	s_node
{
	char					*name;
	struct s_list_of_nodes	*links;
	int						x;
	int						y;
	struct s_node			*bfs_prev;
	int						bfs_used;
	int						bfs_in_queue;
	int						marked;
}				t_node;

typedef struct	s_list_of_nodes
{
	t_node					*node;
	struct s_list_of_nodes	*next;
}				t_list_of_nodes;

/*
**	path - pointer to a path
**	next - pointer to the next element of the list
*/
typedef struct	s_list_of_paths
{
	t_list_of_nodes			*path;
	struct s_list_of_paths	*next;
}				t_list_of_paths;

/*
**	ants - number of ants
**	nodes - list of rooms
**	start - start room
**	end - end room
**	flag_color - print with colors
**	flag_paths - print all intersecting paths
**	flag_steps - print sum of steps in the end
*/

typedef struct	s_lem
{
	int						ants;
	t_list_of_nodes			*nodes;
	t_node					*start;
	t_node					*end;
	int						flag_steps;
	int						flag_color;
	int						flag_paths;
}				t_lem;

/*
**	ant_id - number of ant for printing
**	position - current position of the ant
**	next - pointer to the next element of the list
*/

typedef struct	s_list_of_ants
{
	int						ant_id;
	t_list_of_nodes			*position;
	struct s_list_of_ants	*next;
}				t_list_of_ants;

void			read_map(t_lem *lem);
void			links_mode(char *line, t_lem *lem);
int				get_next_line_counter(int mode, int fd, char **line,
				t_lem *lem);
void			error(char *message, t_lem *lem);
t_node			*create_node(char *line, t_lem *lem);
int				push_node(t_list_of_nodes **list, t_node *node);
t_list_of_nodes	*create_list_of_nodes(t_node *first_node);
t_node			*pop_node(t_list_of_nodes **list);
void			remove_node(t_list_of_nodes **list, t_node *node);
int				node_in_path(t_list_of_nodes *path, t_node *node);
void			create_link(char *line, t_lem *lem);
int				path_len(t_list_of_nodes *list);
void			delete_path(t_list_of_nodes *path);
void			push_path(t_list_of_paths **list, t_list_of_nodes *path);
void			ants_contribution(t_list_of_paths *paths, t_lem *lem);
void			print_steps(t_list_of_ants *ants, t_lem *lem);
void			print_paths(t_list_of_paths *list, t_lem *lem);
void			print_total_steps(int total, t_lem *lem);
void			push_ant(t_list_of_ants **ants, int num,
				t_list_of_nodes *ant_position);
void			remove_ant(t_list_of_ants **ants, t_list_of_ants *ant);
t_list_of_nodes	*bfs(t_lem *lem, int mode);
void			reset_nodes_in_queue(t_list_of_nodes *nodes, t_lem *lem);
void			get_paths(t_list_of_paths **paths_1,
				t_list_of_paths **paths_2, t_lem *lem);
void			sort_paths_by_len(t_list_of_paths *paths);
void			sort_nodes_by_amount_of_links(t_list_of_nodes *nodes);
void			rooms_mode(char *line, int *mode, t_lem *lem);

#endif
