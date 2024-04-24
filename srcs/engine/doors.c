/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 12:40:51 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/24 17:42:09 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static inline double	get_wall_x(t_render *r)
{
	double	wallx;

	if (r->side < 0)
		wallx = r->pos.y + r->pdist * r->ray_dir.y;
	else
		wallx = r->pos.x + r->pdist * r->ray_dir.x;
	wallx -= floor(wallx);
	return (wallx);
}

void	ft_update_door(t_game *g, t_door *door)
{
	if (door->state == OPENING)
		door->frame += 0.01 * (g->now - door->last) / 5000000;
	if (door->frame >= 1.0 && door->state == OPENING)
	{
		door->frame = 1.0;
		door->state = OPEN;
	}
	if (door->state == CLOSING)
		door->frame -= 0.01 * (g->now - door->last) / 5000000;
	if (door->frame <= 0.0 && door->state == CLOSING)
	{
		door->frame = 0.0;
		door->state = CLOSED;
	}
	door->last = g->now;
}

void	ft_door(const t_game *game, t_render *r)
{
	double	wallx;

	r->id = TD;
	r->twidth = game->wt[r->id].width;
	r->s = game->wt[r->id].s;
	wallx = get_wall_x(r);
	r->tex.x = wallx * r->twidth;
	r->linetex.x = wallx * 64;
	r->mystep = (double)r->twidth / r->lh;
	r->linestep = (double)64 / r->lh;
	r->texpos = (r->draw.x - HALF_HEIGHT + r->lh / 2 - game->p.y
			- (int)(game->p.jump) / r->pdist) * r->mystep;
	r->linepos = (r->draw.x - HALF_HEIGHT + r->lh / 2 - game->p.y
			- (int)(game->p.jump) / r->pdist) * r->linestep;
	r->s = game->wt[r->id].s;
}

void	ft_drawdoorpixel(t_thread *t, const int x, const int y, t_render *r)
{
	t_ui	color;

	r->tex.y = (int)r->texpos & (r->twidth - 1);
	r->texpos += r->mystep;
	r->linetex.y = (int)r->linepos & (63);
	r->linepos += r->linestep;
	if (t->g->p.looking && t->g->p.look_pos.x == r->map.x
		&& t->g->p.look_pos.y == r->map.y && (!r->linetex.y
			|| r->linetex.y == 63 || !r->linetex.x || r->linetex.x == 63))
	{
		color = 0x00FF0000;
		*(((unsigned int *)t->g->s.a) + (y * W) + x) = color;
		t->zbuffer[x - t->dx][y] = r->pdist;
		return ;
	}
	if (r->tex.x >= r->twidth * fabs(1 - r->shift))
		return ;
	color = ((int *)t->g->wt[r->id].a)[r->s + r->twidth * r->tex.y + r->tex.x
		+ (int)(r->twidth * r->shift)];
	if ((color & 0x00FFFFFF) == 0)
		return ;
	t->zbuffer[x - t->dx][y] = r->pdist;
	if (*(((unsigned int *)t->g->s.a) + (y * W) + x) != color)
		*(((unsigned int *)t->g->s.a) + (y * W) + x) = color;
}
