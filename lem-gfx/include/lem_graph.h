/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_graph.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzboncak <dzboncak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 21:38:50 by dzboncak          #+#    #+#             */
/*   Updated: 2019/09/03 17:09:46 by dzboncak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_GRAPH_H
# define LEM_GRAPH_H
# include "SDL2/SDL.h"
# include "SDL2/SDL_image.h"
# include "SDL2/SDL_timer.h"
# include "SDL2/SDL_ttf.h"
# include "ft_printf.h"
# include "libft.h"
# include <math.h>

# define WIN_WIDTH 1024
# define WIN_HEIGHT 768
# define ROOM_H 30
# define ROOM_W 30
# define LEM_W 30
# define LEM_H 30

# define ANT_TEX "resources/qt_ant.png"
# define BACK_TEX "resources/background.jpg"

# define GUI_FONT_SIZE 20
# define GUI_W 20
# define GUI_H 10

# define FT_INT_MIN -2147483648
# define FT_INT_MAX 2147483647
# define INIT_SCALE 30
# define OFF_DEL 5
# define ANT_SPEED 60

# define MAP_ROOMS_MODE			0
# define MAP_LINKS_MODE			1
# define MAP_ANTS_MODE			2
# define MAP_STEPS_MODE			3
# define GNL_READ_MODE			0
# define GNL_RETURN_COUNT_MODE	1
# define BFS_ORIGINAL			0
# define BFS_LESS_LINKS			1
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
** Struct for representing a room
*/
typedef struct	s_node
{
	char					*name;
	struct s_list_of_nodes	*links;
	int						x;
	int						y;
	int						draw_x;
	int						draw_y;
	struct s_node			*bfs_prev;
	int						bfs_used;
	int						bfs_in_queue;
	int						marked;
}				t_node;

/*
** List of rooms
*/
typedef struct	s_list_of_nodes
{
	t_node					*node;
	struct s_list_of_nodes	*next;
}				t_list_of_nodes;

/*
** List of steps
** step - 2d array of positions of lem on current step
**	(e.g. step[0] == "L1-s2", step[1] == "L2-s1")
** next - link to next step
*/
typedef	struct				s_list_of_steps
{
	char					**step;
	struct s_list_of_steps	*next;
}							t_list_of_steps;


/*
** List of ants
** id - unique number of ant
** pos - pointer to node where ant is
** next_pos - link to node where ant is moving towards to
** next - link to next ant
*/
typedef struct				s_list_of_ants
{
	int						id;
	t_node					*pos;
	t_node					*next_pos;
	float					x_pos;
	float					y_pos;
	int						finished;
	struct s_list_of_ants	*next;

}							t_list_of_ants;

/*
** Struct for lem-in solution
*/
typedef struct				s_lem
{
	int						ants_count;
	int						ants_finished;
	t_list_of_ants			*ants;
	t_list_of_nodes			*nodes;
	t_list_of_steps			*steps;
	t_list_of_steps			*cur_step;
	t_node					*start;
	t_node					*end;
	int						flag_steps;
	int						flag_color;
	int						flag_paths;
}							t_lem;

/*
** Main struct for visualizing lem-in
** (win, rend) - members of window an renderer
** (lem, background, room) - textures for drawing
**	lem_data - actual lem-in data (rooms, links, ants)
*/
typedef struct				s_visual
{
	SDL_Window				*win;
	SDL_Renderer			*rend;
	SDL_Texture				*ant;
	SDL_Texture				*background;
	SDL_Texture				*room;
	t_lem					*lem_data;
	int						x_off;
	int						y_off;
	int						scale;
	unsigned int			step_speed;

}							t_visual;


/*
** SDL dependent funcs
*/
int							init_sdl(t_visual *vis);
SDL_Texture					*load_tex(const char *file_name, t_visual *vis);
void						apply_surface(int x, int y, SDL_Texture *tex,
							SDL_Renderer *rend);

/*
** Reading funcs
*/
void						read_map(t_lem *lem);
void						links_mode(char *line, t_lem *lem);
int							get_next_line_counter(int mode,
							int fd, char **line, t_lem *lem);
void						error(char *message, t_lem *lem);
t_node						*create_node(char *line, t_lem *lem);
int							push_node(t_list_of_nodes **list, t_node *node);
t_list_of_nodes				*create_list_of_nodes(t_node *first_node);
t_node						*pop_node(t_list_of_nodes **list);
void						remove_node(t_list_of_nodes **list, t_node *node);
int							node_in_path(t_list_of_nodes *path, t_node *node);
void						create_link(char *line, t_lem *lem);
void						rooms_mode(char *line, int *mode, t_lem *lem);
void						create_link(char *line, t_lem *lem);
void						steps_mode(char *line, t_lem *lem);

/*
** Drawing funcs
*/
void						draw_all(t_visual *vis);
void						draw_ants(t_visual *vis);
void						put_text(SDL_Renderer *rend, int x, int y,
							char *text_msg);

/*
** Moving ants
*/
void						update_x_y(t_list_of_ants *ant, SDL_Rect *rect);
int							is_finished(t_list_of_ants *ant,
							t_list_of_steps *cur, t_list_of_nodes *room);
int							step_done(t_list_of_ants *ant);
t_node						*get_next_pos(char *str, t_list_of_nodes *room);
int							get_id(char *str);
void						remove_ant(t_list_of_ants **ants,
							t_list_of_ants *ant);
void						set_unfinished(t_list_of_ants *ant);
int							move_ant(t_list_of_ants *ant,
							t_list_of_steps *cr_step, t_visual *vis);

/*
** Debug funcs
*/
void						print_steps(t_lem *lem);
void						print_ants(t_lem *lem);

/*
** Misc
*/
int							ft_lstlen(t_list_of_nodes *start);
void						calc_offset(t_visual *vis, t_list_of_nodes *cur);

#endif
