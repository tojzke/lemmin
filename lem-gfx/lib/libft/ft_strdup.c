/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkiehn <bkiehn@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 19:14:58 by bkiehn            #+#    #+#             */
/*   Updated: 2019/03/24 17:15:10 by bkiehn           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	size_t	n;
	char	*cop;

	if (s1 == 0)
		return (0);
	n = ft_strlen(s1) + 1;
	i = 0;
	if ((cop = (char*)malloc(sizeof(char) * n)) == NULL)
		return (NULL);
	while (n--)
	{
		cop[i] = s1[i];
		i++;
	}
	return (cop);
}
