/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_count.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzboncak <dzboncak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 17:06:45 by dzboncak          #+#    #+#             */
/*   Updated: 2019/07/11 17:06:59 by dzboncak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int		ft_char_count(char c, char *line)
{
	int i;
	int res;

	res = 0;
	i = -1;
	while (line[++i])
	{
		if (line[i] == c)
			res++;
	}
	return (res);
}
