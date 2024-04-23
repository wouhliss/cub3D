/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectile_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 03:21:13 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/23 12:08:50 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

bool	ft_projectile_hit(t_game *g, t_projectile *p)
{
	if (!ft_outside(g, p->map.x, p->map.y)
		&& !ft_can_step(g, p->sprite))
	{
		p->sprite->hide = 1;
		p->sprite->delete = 1;
		p->delete = 1;
		return (true);
	}
	return (false);
}
