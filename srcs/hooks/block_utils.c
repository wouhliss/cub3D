/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 23:18:11 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/24 17:55:06 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_remove_door(t_game *g, t_door *door)
{
	g->map.map[door->pos.y][door->pos.x] = '0';
	door->delete = true;
}

char	ft_get_block(t_game *g)
{
	const char	blocks[] = {'1', 's', 'D', 'g', 'o', 'a', 'n', 'm', 'c', 'g',
			'v', 'A', 'G', 'l', 'V', 'O', 'r', 'M', 'R', 't', 'w', 'j'};

	return (blocks[g->p.weapon.state]);
}
