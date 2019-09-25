/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzboncak <dzboncak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 21:36:09 by dzboncak          #+#    #+#             */
/*   Updated: 2019/09/03 17:24:09 by dzboncak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_graph.h"

int			init_window(t_visual *vis)
{
	vis->win = SDL_CreateWindow("lem-gfx", SDL_WINDOWPOS_CENTERED,
	SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, 0);
	if (vis->win == NULL)
	{
		ft_printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
		SDL_DestroyWindow(vis->win);
		SDL_Quit();
		return (0);
	}
	return (1);
}

int			init_render(t_visual *vis)
{
	Uint32	render_flags;

	render_flags = SDL_RENDERER_ACCELERATED |
	SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE;
	vis->rend = SDL_CreateRenderer(vis->win, -1, render_flags);
	if (vis->rend == NULL)
	{
		ft_printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
		SDL_DestroyWindow(vis->win);
		SDL_DestroyRenderer(vis->rend);
		SDL_Quit();
		return (0);
	}
	return (1);
}

int			init_text(t_visual *vis)
{
	vis->ant = load_tex(ANT_TEX, vis);
	if (vis->ant == NULL)
	{
		ft_printf("Error loading bg or lem texture: %s\n", SDL_GetError());
		SDL_DestroyRenderer(vis->rend);
		SDL_DestroyWindow(vis->win);
		SDL_Quit();
		return (0);
	}
	vis->background = load_tex(BACK_TEX, vis);
	return (1);
}

int			init_sdl(t_visual *vis)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	if (!init_window(vis))
		exit(1);
	if (!init_render(vis))
		exit(1);
	if (!init_text(vis))
		exit(1);
	return (0);
}
