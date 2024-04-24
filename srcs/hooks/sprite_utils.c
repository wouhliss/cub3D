/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 19:48:15 by ybelatar          #+#    #+#             */
/*   Updated: 2024/04/24 19:49:20 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_place_sprite(t_game *g)
{
	t_sprite	sprite;

	if (g->p.weapon.state == 0)
		sprite = (t_sprite){.t = 0, .vdiff = 0.0, .hr = 1, .vr = 1, .hide = 0,
			.pos = g->p.pos};
	else if (g->p.weapon.state == 1)
		sprite = (t_sprite){.t = 1, .vdiff = 0.0, .hr = 1, .vr = 1,
			.pos = g->p.pos};
	else if (g->p.weapon.state == 2)
	{
		sprite = (t_sprite){.t = 1, .vdiff = 0.0, .hr = 2, .vr = 2,
			.pos = g->p.pos};
		sprite.vdiff = HEIGHT / (sprite.vr * 2);
	}
	ft_add_to_vector(g, &g->sprites, &sprite);
}
