/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzboncak <dzboncak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 20:28:52 by dzboncak          #+#    #+#             */
/*   Updated: 2019/08/02 20:09:09 by dzboncak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_graph.h"

SDL_Texture		*load_tex(const char *file_name, t_visual *vis)
{
	SDL_Surface	*loaded_image;
	SDL_Texture	*tex;
	Uint32		colorkey;

	loaded_image = IMG_Load(file_name);
	if (loaded_image != NULL)
	{
		if (ft_strequ(file_name, ANT_TEX))
		{
			colorkey = SDL_MapRGB(loaded_image->format, 0xFF, 0xFF, 0xFF);
			SDL_SetColorKey(loaded_image, SDL_TRUE, colorkey);
		}
		tex = SDL_CreateTextureFromSurface(vis->rend, loaded_image);
		SDL_FreeSurface(loaded_image);
	}
	else
	{
		ft_printf("Can't create texture %s\n", SDL_GetError());
		return (NULL);
	}
	return (tex);
}
