/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 16:07:39 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/24 19:57:36 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ic(char *charset, char c)
{
	while (*charset)
	{
		if (*charset == c)
			return (1);
		++charset;
	}
	return (0);
}

t_vec	ft_side_to_dir(const int side)
{
	t_vec	dir;

	dir = (t_vec){0, 0};
	if (side == -2)
		dir = (t_vec){-1, 0};
	else if (side == -1)
		dir = (t_vec){1, 0};
	else if (side == 2)
		dir = (t_vec){0, 1};
	else if (side == 1)
		dir = (t_vec){0, -1};
	return (dir);
}

t_vec	ft_side_to_plane(const int side)
{
	t_vec	p;

	p = (t_vec){0, 0};
	if (side == -2)
		p = (t_vec){0, 0.66};
	else if (side == -1)
		p = (t_vec){0, -0.66};
	else if (side == 2)
		p = (t_vec){0.66, 0};
	else if (side == 1)
		p = (t_vec){-0.66, 0};
	return (p);
}
