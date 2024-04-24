/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 23:18:11 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/24 21:53:50 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_remove_door(t_game *g, t_door *door)
{
	g->m.m[door->pos.y][door->pos.x] = '0';
	door->delete = true;
}

char	ft_get_block(t_game *g)
{
	const char	blocks[] = {'1', 's', 'D', 't', 'e', 'r', 'y', 'u', 'i', 'o',
		'p', 'a', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'z', 'x'};

	return (blocks[g->p.weapon.state]);
}
