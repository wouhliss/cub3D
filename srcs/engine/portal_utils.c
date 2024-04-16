/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 00:45:09 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/16 03:06:54 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_portal_1(t_render *r, const t_game *g)
{
	int		temp;
	double	dtemp;

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

void	ft_portal_2(t_render *r, const t_game *g)
{
	int		temp;
	double	dtemp;

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

void	ft_portal_3(t_render *r, const t_game *g)
{
	int		temp;
	double	dtemp;

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

void	ft_portal_4(t_render *r, const t_game *g)
{
	int		temp;
	double	dtemp;

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

void	ft_portal_hit(t_thread *t, const t_game *g, t_render *r)
{
	t_hit	hit;

	hit.render = *r;
	if (r->map.x == g->portal_l.pos.x && r->map.y == g->portal_l.pos.y
		&& r->side == g->portal_l.side)
		hit.render.hit = 4;
	else if (r->map.x == g->portal_r.pos.x && r->map.y == g->portal_r.pos.y
		&& r->side == g->portal_r.side)
		hit.render.hit = 5;
	else
		return ;
	if (hit.render.hit == 4)
		ft_portal_l(g, r, &hit);
	else if (hit.render.hit == 5)
		ft_portal_r(g, r, &hit);
	ft_add_to_vector(t->g, &t->hit, &hit);
}
