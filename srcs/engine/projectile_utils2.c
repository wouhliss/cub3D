/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectile_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 03:21:13 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/24 19:55:43 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

bool	ft_projectile_hit(t_game *g, t_projectile *p)
{
	if (!ft_outside(g, p->m.x, p->m.y)
		&& !ft_can_step(g, p->sprite))
	{
		p->sprite->hide = 1;
		p->sprite->delete = 1;
		p->delete = 1;
		return (true);
	}
	return (false);
}
