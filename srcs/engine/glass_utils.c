/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glass_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 21:45:07 by ybelatar          #+#    #+#             */
/*   Updated: 2024/04/24 21:52:22 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static inline int	ft_get_glass_id_2(const char c)
{
	if (c == 'h')
		return (12);
	else if (c == 'j')
		return (13);
	else if (c == 'k')
		return (14);
	else if (c == 'l')
		return (15);
	else if (c == 'z')
		return (16);
	else if (c == 'x')
		return (17);
	return (0);
}

int	ft_get_glass_id(const char c)
{
	if (c == 't')
		return (0);
	else if (c == 'e')
		return (1);
	else if (c == 'r')
		return (2);
	else if (c == 'y')
		return (3);
	else if (c == 'u')
		return (4);
	else if (c == 'i')
		return (5);
	else if (c == 'o')
		return (6);
	else if (c == 'p')
		return (7);
	else if (c == 'a')
		return (8);
	else if (c == 'd')
		return (9);
	else if (c == 'f')
		return (10);
	else if (c == 'g')
		return (11);
	return (ft_get_glass_id_2(c));
}
