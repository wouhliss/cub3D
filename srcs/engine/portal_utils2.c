/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 03:03:56 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/16 03:08:33 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_portal_l(const t_game *g, t_render *r, t_hit *hit)
{
	if (g->portal_r.side)
	{
		r->map.x = g->portal_r.pos.x;
		r->map.y = g->portal_r.pos.y;
		if (r->side < 0 && g->portal_r.side < 0)
		{
			if (r->side == g->portal_r.side)
				r->step.x = -r->step.x;
			r->map.x += r->step.x;
		}
		else if (r->side > 0 && g->portal_r.side > 0)
		{
			if (r->side == g->portal_r.side)
				r->step.y = -r->step.y;
			r->map.y += r->step.y;
		}
		else if (r->side < 0 && g->portal_r.side > 0)
			ft_portal_1(r, g);
		else
			ft_portal_2(r, g);
		hit->render.hit = 6;
	}
}

void	ft_portal_r(const t_game *g, t_render *r, t_hit *hit)
{
	if (g->portal_l.side)
	{
		r->map.x = g->portal_l.pos.x;
		r->map.y = g->portal_l.pos.y;
		if (r->side < 0 && g->portal_l.side < 0)
		{
			if (r->side == g->portal_l.side)
				r->step.x = -r->step.x;
			r->map.x += r->step.x;
		}
		else if (r->side > 0 && g->portal_l.side > 0)
		{
			if (r->side == g->portal_l.side)
				r->step.y = -r->step.y;
			r->map.y += r->step.y;
		}
		else if (r->side < 0 && g->portal_l.side > 0)
			ft_portal_3(r, g);
		else
			ft_portal_4(r, g);
		hit->render.hit = 7;
	}
}
