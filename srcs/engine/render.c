/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 16:55:26 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/02 18:09:42 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static inline void	ft_steps(const t_game *game, t_render *render)
{
	if (render->ray_dir.x < 0)
	{
		render->step.x = -1;
		render->side_dist.x = (game->p.pos.x - render->map.x)
			* render->delta_dist.x;
	}
	else
	{
		render->step.x = 1;
		render->side_dist.x = (render->map.x + 1.0 - game->p.pos.x)
			* render->delta_dist.x;
	}
	if (render->ray_dir.y < 0)
	{
		render->step.y = -1;
		render->side_dist.y = (game->p.pos.y - render->map.y)
			* render->delta_dist.y;
	}
	else
	{
		render->step.y = 1;
		render->side_dist.y = (render->map.y + 1.0 - game->p.pos.y)
			* render->delta_dist.y;
	}
}

static inline void	ft_door(const t_game *game, t_render *render)
{
	t_door	*door;

	door = game->doors;
	while (door)
	{
		if (door->pos.x == render->map.x && door->pos.y == render->map.y)
		{
			render->door = door;
			break ;
		}
		door = door->next;
	}
	render->dhit = 1;
	render->dside_dist.x = render->side_dist.x;
	render->dside_dist.y = render->side_dist.y;
	render->dside = render->side;
	if (render->dside > 0)
		render->dperp_dist = (render->dside_dist.y + render->delta_dist.y / 2)
			- render->delta_dist.y;
	else
		render->dperp_dist = (render->dside_dist.x + render->delta_dist.x / 2)
			- render->delta_dist.x;
	render->dline_height = (int)(HEIGHT / render->dperp_dist);
	render->ddraw.x = -render->dline_height / 2 + HALF_HEIGHT + game->p.y
		+ (int)(game->p.jump) / render->dperp_dist;
	if (render->ddraw.x < 0)
		render->ddraw.x = 0;
	render->ddraw.y = render->dline_height / 2 + HALF_HEIGHT + game->p.y
		+ (int)(game->p.jump) / render->dperp_dist;
	if (render->ddraw.y >= HEIGHT)
		render->ddraw.y = HEIGHT - 1;
}

static inline void	ft_glass(const t_game *game, t_render *render)
{
	render->thit = 1;
	render->tside_dist.x = render->side_dist.x;
	render->tside_dist.y = render->side_dist.y;
	render->tside = render->side;
	if (render->tside > 0)
		render->tperp_dist = render->tside_dist.y - render->delta_dist.y;
	else
		render->tperp_dist = render->tside_dist.x - render->delta_dist.x;
	render->tline_height = (int)(HEIGHT / render->tperp_dist);
	render->tdraw.x = -render->tline_height / 2 + HALF_HEIGHT + game->p.y
		+ (int)(game->p.jump) / render->tperp_dist;
	if (render->tdraw.x < 0)
		render->tdraw.x = 0;
	render->tdraw.y = render->tline_height / 2 + HALF_HEIGHT + game->p.y
		+ (int)(game->p.jump) / render->tperp_dist;
	if (render->tdraw.y >= HEIGHT)
		render->tdraw.y = HEIGHT - 1;
}

static inline void	ft_portal(const t_game *game, t_render *render)
{
	double	dtemp;
	int		temp;

	if (render->map.x == game->portal_l.pos.x
		&& render->map.y == game->portal_l.pos.y
		&& render->side == game->portal_l.side)
		render->phit = 1;
	else if (render->map.x == game->portal_r.pos.x
		&& render->map.y == game->portal_r.pos.y
		&& render->side == game->portal_r.side)
		render->phit = 2;
	else
		return ;
	if (!render->portal)
	{
		render->pside_dist.x = render->side_dist.x;
		render->pside_dist.y = render->side_dist.y;
		render->pside = render->side;
		if (render->pside > 0)
			render->pperp_dist = render->pside_dist.y - render->delta_dist.y;
		else
			render->pperp_dist = render->pside_dist.x - render->delta_dist.x;
		render->pline_height = (int)(HEIGHT / render->pperp_dist);
		render->pdraw.x = -render->pline_height / 2 + HALF_HEIGHT + game->p.y
			+ (int)(game->p.jump) / render->pperp_dist;
		if (render->pdraw.x < 0)
			render->pdraw.x = 0;
		render->pdraw.y = render->pline_height / 2 + HALF_HEIGHT + game->p.y
			+ (int)(game->p.jump) / render->pperp_dist;
		if (render->pdraw.y >= HEIGHT)
			render->pdraw.y = HEIGHT - 1;
		render->portal = 1;
	}
	if (render->phit == 1)
	{
		if (game->portal_r.side)
		{
			render->map.x = game->portal_r.pos.x;
			render->map.y = game->portal_r.pos.y;
			if (render->side < 0 && game->portal_r.side < 0)
			{
				if (render->side == game->portal_r.side)
					render->step.x = -render->step.x;
				render->map.x += render->step.x;
			}
			else if (render->side > 0 && game->portal_r.side > 0)
			{
				if (render->side == game->portal_r.side)
					render->step.y = -render->step.y;
				render->map.y += render->step.y;
			}
			else if (render->side < 0 && game->portal_r.side > 0)
			{
				dtemp = render->delta_dist.x;
				render->delta_dist.x = render->delta_dist.y;
				render->delta_dist.y = dtemp;
				dtemp = render->side_dist.x;
				render->side_dist.x = render->side_dist.y;
				render->side_dist.y = dtemp;
				temp = render->step.x;
				render->step.x = render->step.y;
				if (render->side == -game->portal_r.side)
					render->step.y = -temp;
				else
					render->step.y = temp;
				render->map.y += render->step.y;
				render->side = game->portal_r.side;
				dtemp = render->ray_dir.x;
				render->ray_dir.x = render->ray_dir.y;
				render->ray_dir.y = dtemp;
				dtemp = render->pos.x;
				render->pos.x = render->pos.y;
				render->pos.y = dtemp;
			}
			else
			{
				dtemp = render->delta_dist.x;
				render->delta_dist.x = render->delta_dist.y;
				render->delta_dist.y = dtemp;
				dtemp = render->side_dist.x;
				render->side_dist.x = render->side_dist.y;
				render->side_dist.y = dtemp;
				temp = render->step.y;
				render->step.y = render->step.x;
				if (render->side == -game->portal_r.side)
					render->step.x = -temp;
				else
					render->step.x = temp;
				render->map.x += render->step.x;
				render->side = game->portal_r.side;
				dtemp = render->ray_dir.x;
				render->ray_dir.x = render->ray_dir.y;
				render->ray_dir.y = dtemp;
				dtemp = render->pos.x;
				render->pos.x = render->pos.y;
				render->pos.y = dtemp;
			}
			render->phit = 3;
		}
	}
	else if (render->phit == 2)
	{
		if (game->portal_l.side)
		{
			render->map.x = game->portal_l.pos.x;
			render->map.y = game->portal_l.pos.y;
			if (render->side < 0 && game->portal_l.side < 0)
			{
				if (render->side == game->portal_l.side)
					render->step.x = -render->step.x;
				render->map.x += render->step.x;
			}
			else if (render->side > 0 && game->portal_l.side > 0)
			{
				if (render->side == game->portal_l.side)
					render->step.y = -render->step.y;
				render->map.y += render->step.y;
			}
			else if (render->side < 0 && game->portal_l.side > 0)
			{
				dtemp = render->delta_dist.x;
				render->delta_dist.x = render->delta_dist.y;
				render->delta_dist.y = dtemp;
				dtemp = render->side_dist.x;
				render->side_dist.x = render->side_dist.y;
				render->side_dist.y = dtemp;
				temp = render->step.x;
				render->step.x = render->step.y;
				if (render->side == -game->portal_l.side)
					render->step.y = -temp;
				else
					render->step.y = temp;
				render->map.y += render->step.y;
				render->side = game->portal_l.side;
				dtemp = render->ray_dir.x;
				render->ray_dir.x = render->ray_dir.y;
				render->ray_dir.y = dtemp;
				dtemp = render->pos.x;
				render->pos.x = render->pos.y;
				render->pos.y = dtemp;
			}
			else
			{
				dtemp = render->delta_dist.x;
				render->delta_dist.x = render->delta_dist.y;
				render->delta_dist.y = dtemp;
				dtemp = render->side_dist.x;
				render->side_dist.x = render->side_dist.y;
				render->side_dist.y = dtemp;
				temp = render->step.y;
				render->step.y = render->step.x;
				if (render->side == -game->portal_l.side)
					render->step.x = -temp;
				else
					render->step.x = temp;
				render->map.x += render->step.x;
				render->side = game->portal_l.side;
				dtemp = render->ray_dir.x;
				render->ray_dir.x = render->ray_dir.y;
				render->ray_dir.y = dtemp;
				dtemp = render->pos.x;
				render->pos.x = render->pos.y;
				render->pos.y = dtemp;
			}
			render->phit = 4;
		}
	}
}

static inline void	ft_dda(const t_game *game, t_render *render)
{
	while (!render->hit && !ft_outside(game, render->map.x, render->map.y))
	{
		if (render->side_dist.x < render->side_dist.y)
		{
			render->side_dist.x += render->delta_dist.x;
			render->map.x += render->step.x;
			render->side = -1;
			if (render->step.x < 0)
				render->side = -2;
		}
		else
		{
			render->side_dist.y += render->delta_dist.y;
			render->map.y += render->step.y;
			render->side = 1;
			if (render->step.y < 0)
				render->side = 2;
		}
		ft_portal(game, render);
		if (!ft_outside(game, render->map.x, render->map.y)
			&& game->map.map[render->map.y][render->map.x] == '1')
			render->hit = 1;
		else if (!render->dhit && !ft_outside(game, render->map.x,
				render->map.y)
			&& game->map.map[render->map.y][render->map.x] == 'D'
			&& render->side > 0)
			ft_door(game, render);
		else if (!render->thit && !ft_outside(game, render->map.x,
				render->map.y)
			&& game->map.map[render->map.y][render->map.x] == 't')
			ft_glass(game, render);
	}
}

static inline void	ft_rays(const t_game *game, t_render *render, const int x)
{
	render->camera_x = 2.0 * x / ((double)WIDTH) - 1.0;
	render->pos = game->p.pos;
	render->ray_dir = (t_vec){-(game->p.dir.x + game->p.p.x * render->camera_x),
		game->p.dir.y + game->p.p.y * render->camera_x};
	render->map = (t_intvec){(int)game->p.pos.x, (int)game->p.pos.y};
	render->delta_dist = (t_vec){1e30, 1e30};
	if (render->ray_dir.x)
		render->delta_dist.x = fabs(1.0 / render->ray_dir.x);
	if (render->ray_dir.y)
		render->delta_dist.y = fabs(1.0 / render->ray_dir.y);
	render->hit = 0;
	render->phit = 0;
	render->thit = 0;
	render->dhit = 0;
	render->portal = 0;
	ft_steps(game, render);
	ft_dda(game, render);
	if (render->side > 0)
		render->perp_dist = render->side_dist.y - render->delta_dist.y;
	else
		render->perp_dist = render->side_dist.x - render->delta_dist.x;
	render->line_height = (int)(HEIGHT / render->perp_dist);
	render->draw.x = -render->line_height / 2 + HALF_HEIGHT + game->p.y
		+ (int)(game->p.jump) / render->perp_dist;
	if (render->draw.x < 0)
		render->draw.x = 0;
	render->draw.y = render->line_height / 2 + HALF_HEIGHT + game->p.y
		+ (int)(game->p.jump) / render->perp_dist;
	if (render->draw.y >= HEIGHT)
		render->draw.y = HEIGHT - 1;
}

static inline void	ft_draw(t_game *game, const int w, const int dx)
{
	t_render	r;

	ft_floorceil(game, w, dx);
	r.pixel.x = dx - 1;
	while (++r.pixel.x < w)
	{
		ft_rays(game, &r, r.pixel.x);
		ft_wall(game, &r);
		if (r.dhit)
			ft_dwall(game, &r);
		r.pixel.y = -1;
		while (++r.pixel.y < HEIGHT)
		{
			game->zbuffer[r.pixel.x][r.pixel.y] = r.perp_dist;
			// if (r.pixel.y < r.draw.x)
			// 	my_mlx_pixel_put(&game->screen, r.pixel.x, r.pixel.y,
			// 		game->map.c_color);
			if (r.pixel.y >= r.draw.x && r.pixel.y <= r.draw.y)
				ft_drawpixel(game, r.pixel.x, r.pixel.y, &r);
			// else
			// 	my_mlx_pixel_put(&game->screen, r.pixel.x, r.pixel.y,
			// 		game->map.f_color);
			if (r.thit && r.pixel.y >= r.tdraw.x && r.pixel.y <= r.tdraw.y)
				my_mlx_pixel_tput(&game->screen, r.pixel.x, r.pixel.y,
					create_trgb(0, 127, 127, 127));
			if (r.dhit && r.pixel.y >= r.ddraw.x && r.pixel.y <= r.ddraw.y)
				ft_ddrawpixel(game, r.pixel.x, r.pixel.y, &r);
			if (r.phit == 1 && r.pixel.y >= r.pdraw.x && r.pixel.y <= r.pdraw.y)
				my_mlx_pixel_put(&game->screen, r.pixel.x, r.pixel.y,
					create_trgb(0, 0, 127, 255));
			if (r.phit == 2 && r.pixel.y >= r.pdraw.x && r.pixel.y <= r.pdraw.y)
				my_mlx_pixel_put(&game->screen, r.pixel.x, r.pixel.y,
					create_trgb(0, 255, 127, 0));
			if (r.phit == 3 && (r.pixel.y == r.pdraw.x || r.pixel.y == r.pdraw.y))
				my_mlx_pixel_put(&game->screen, r.pixel.x, r.pixel.y,
					create_trgb(0, 0, 127, 255));
			if (r.phit == 4 && (r.pixel.y == r.pdraw.x || r.pixel.y == r.pdraw.y))
				my_mlx_pixel_put(&game->screen, r.pixel.x, r.pixel.y,
					create_trgb(0, 255, 127, 0));
		}
	}
	ft_drawsprites(game, w, dx);
}

void	*ft_thread(void *arg)
{
	t_thread	*t;
	t_game		*game;

	t = arg;
	game = t->game;
	pthread_mutex_lock(&game->state_m);
	while (game->state != ENDED)
	{
		pthread_mutex_lock(&game->rendered_m[t->id]);
		while (game->state != RENDERING || game->rendered[t->id])
		{
			if (game->state == ENDED)
			{
				pthread_mutex_unlock(&game->state_m);
				pthread_mutex_unlock(&game->rendered_m[t->id]);
				return (NULL);
			}
			pthread_mutex_unlock(&game->state_m);
			pthread_mutex_unlock(&game->rendered_m[t->id]);
			usleep(100);
			pthread_mutex_lock(&game->state_m);
			pthread_mutex_lock(&game->rendered_m[t->id]);
		}
		pthread_mutex_unlock(&game->state_m);
		pthread_mutex_unlock(&game->rendered_m[t->id]);
		ft_draw(game, (t->id + 1) * Q_WIDTH, t->id * Q_WIDTH);
		pthread_mutex_lock(&game->rendered_m[t->id]);
		game->rendered[t->id] = 1;
		pthread_mutex_unlock(&game->rendered_m[t->id]);
		pthread_mutex_lock(&game->state_m);
	}
	pthread_mutex_unlock(&game->state_m);
	return (NULL);
}
