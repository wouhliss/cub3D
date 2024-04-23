/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 23:18:11 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/23 11:30:45 by wouhliss         ###   ########.fr       */
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
	const int	blocks[] = {'1', 't', 's', 'D'};

	return (blocks[g->p.weapon.state]);
}
