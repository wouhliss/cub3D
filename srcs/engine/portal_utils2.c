/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 03:03:56 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/24 22:41:59 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_portal_l(const t_game *g, t_render *r, t_hit *hit)
{
	if (g->pr.side)
	{
		r->m.x = g->pr.pos.x;
		r->m.y = g->pr.pos.y;
		if (r->side < 0 && g->pr.side < 0)
		{
			if (r->side == g->pr.side)
				r->step.x = -r->step.x;
			r->m.x += r->step.x;
		}
		else if (r->side > 0 && g->pr.side > 0)
		{
			if (r->side == g->pr.side)
				r->step.y = -r->step.y;
			r->m.y += r->step.y;
		}
		else if (r->side < 0 && g->pr.side > 0)
			ft_portal_1(r, g);
		else
			ft_portal_2(r, g);
		hit->render.hit = 6;
	}
}

void	ft_portal_r(const t_game *g, t_render *r, t_hit *hit)
{
	if (g->pl.side)
	{
		r->m.x = g->pl.pos.x;
		r->m.y = g->pl.pos.y;
		if (r->side < 0 && g->pl.side < 0)
		{
			if (r->side == g->pl.side)
				r->step.x = -r->step.x;
			r->m.x += r->step.x;
		}
		else if (r->side > 0 && g->pl.side > 0)
		{
			if (r->side == g->pl.side)
				r->step.y = -r->step.y;
			r->m.y += r->step.y;
		}
		else if (r->side < 0 && g->pl.side > 0)
			ft_portal_3(r, g);
		else
			ft_portal_4(r, g);
		hit->render.hit = 7;
	}
}

void	ft_update_doors_portals(t_game *g)
{
	t_intvec	facing;

	ft_check_door(g);
	if (g->p.looking_side < 0 && g->p.step.x < 0)
		g->p.looking_side = -2;
	if (g->p.looking_side > 0 && g->p.step.y < 0)
		g->p.looking_side = 2;
	if (g->m.m[g->pl.pos.y][g->pl.pos.x] != '1')
		g->pl.side = 0;
	if (g->m.m[g->pr.pos.y][g->pr.pos.x] != '1')
		g->pr.side = 0;
	facing = ft_get_facing_int(g->pl.side, g->pl.pos);
	if (g->m.m[facing.y][facing.x] != '0')
		g->pl.side = 0;
	facing = ft_get_facing_int(g->pr.side, g->pr.pos);
	if (g->m.m[facing.y][facing.x] != '0')
		g->pr.side = 0;
}
