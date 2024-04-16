/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 00:45:09 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/16 02:04:30 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_portal_hit(t_thread *t, const t_game *g, t_render *r)
{
	t_hit		hit;
	double		dtemp;
	int			temp;

	hit.render = *r;
	if (r->map.x == g->portal_l.pos.x
		&& r->map.y == g->portal_l.pos.y
		&& r->side == g->portal_l.side)
		hit.render.hit = 4;
	else if (r->map.x == g->portal_r.pos.x
		&& r->map.y == g->portal_r.pos.y
		&& r->side == g->portal_r.side)
		hit.render.hit = 5;
	else
		return ;
	if (hit.render.hit == 4)
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
			{
				dtemp = r->dd.x;
				r->dd.x = r->dd.y;
				r->dd.y = dtemp;
				dtemp = r->sd.x;
				r->sd.x = r->sd.y;
				r->sd.y = dtemp;
				temp = r->step.x;
				r->step.x = r->step.y;
				if (r->side == -g->portal_r.side)
					r->step.y = -temp;
				else
					r->step.y = temp;
				r->map.y += r->step.y;
				r->side = g->portal_r.side;
				dtemp = r->ray_dir.x;
				r->ray_dir.x = r->ray_dir.y;
				r->ray_dir.y = dtemp;
				dtemp = r->pos.x;
				r->pos.x = r->pos.y;
				r->pos.y = dtemp;
			}
			else
			{
				dtemp = r->dd.x;
				r->dd.x = r->dd.y;
				r->dd.y = dtemp;
				dtemp = r->sd.x;
				r->sd.x = r->sd.y;
				r->sd.y = dtemp;
				temp = r->step.y;
				r->step.y = r->step.x;
				if (r->side == -g->portal_r.side)
					r->step.x = -temp;
				else
					r->step.x = temp;
				r->map.x += r->step.x;
				r->side = g->portal_r.side;
				dtemp = r->ray_dir.x;
				r->ray_dir.x = r->ray_dir.y;
				r->ray_dir.y = dtemp;
				dtemp = r->pos.x;
				r->pos.x = r->pos.y;
				r->pos.y = dtemp;
			}
			hit.render.hit = 6;
		}
	}
	else if (hit.render.hit == 5)
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
			{
				dtemp = r->dd.x;
				r->dd.x = r->dd.y;
				r->dd.y = dtemp;
				dtemp = r->sd.x;
				r->sd.x = r->sd.y;
				r->sd.y = dtemp;
				temp = r->step.x;
				r->step.x = r->step.y;
				if (r->side == -g->portal_l.side)
					r->step.y = -temp;
				else
					r->step.y = temp;
				r->map.y += r->step.y;
				r->side = g->portal_l.side;
				dtemp = r->ray_dir.x;
				r->ray_dir.x = r->ray_dir.y;
				r->ray_dir.y = dtemp;
				dtemp = r->pos.x;
				r->pos.x = r->pos.y;
				r->pos.y = dtemp;
			}
			else
			{
				dtemp = r->dd.x;
				r->dd.x = r->dd.y;
				r->dd.y = dtemp;
				dtemp = r->sd.x;
				r->sd.x = r->sd.y;
				r->sd.y = dtemp;
				temp = r->step.y;
				r->step.y = r->step.x;
				if (r->side == -g->portal_l.side)
					r->step.x = -temp;
				else
					r->step.x = temp;
				r->map.x += r->step.x;
				r->side = g->portal_l.side;
				dtemp = r->ray_dir.x;
				r->ray_dir.x = r->ray_dir.y;
				r->ray_dir.y = dtemp;
				dtemp = r->pos.x;
				r->pos.x = r->pos.y;
				r->pos.y = dtemp;
			}
			hit.render.hit = 7;
		}
	}
	ft_add_to_vector(t->g, &t->hit, &hit);
}
