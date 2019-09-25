/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzboncak <dzboncak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 21:36:15 by dzboncak          #+#    #+#             */
/*   Updated: 2019/08/02 20:40:28 by dzboncak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_graph.h"

static t_lem	*init_lem(void)
{
	t_lem *lem;

	lem = ft_memalloc(sizeof(t_lem));
	lem->nodes = NULL;
	lem->start = NULL;
	lem->end = NULL;
	lem->flag_color = 0;
	lem->steps = NULL;
	lem->cur_step = NULL;
	return (lem);
}

static void		calc_draw_fact(t_visual *vis)
{
	int		room_numb;

	room_numb = ft_lstlen(vis->lem_data->nodes);
	calc_offset(vis, vis->lem_data->nodes);
	vis->scale = INIT_SCALE;
}

static void		init_all(t_visual *vis)
{
	ft_memset(vis, 0, sizeof(t_visual));
	vis->lem_data = init_lem();
	vis->step_speed = 2000;
	read_map(vis->lem_data);
	if (vis->lem_data->nodes == NULL)
		error("No map given!", vis->lem_data);
	calc_draw_fact(vis);
	init_sdl(vis);
	TTF_Init();
}

int				main(void)
{
	t_visual	vis;
	SDL_Event	event;
	SDL_bool	is_running;

	init_all(&vis);
	is_running = SDL_TRUE;
	print_steps(vis.lem_data);
	while (is_running)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				is_running = SDL_FALSE;
		}
		draw_all(&vis);
	}
	SDL_DestroyWindow(vis.win);
	SDL_Quit();
}
