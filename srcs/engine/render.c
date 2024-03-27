/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 16:55:26 by wouhliss          #+#    #+#             */
/*   Updated: 2024/03/27 16:21:24 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static inline void	ft_dda(t_game *game, t_render *render)
{
	while (!render->hit && render->map.y < game->length
		&& render->map.x < game->width && render->map.x > 0
		&& render->map.y > 0)
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
		if (game->map.map[render->map.y][render->map.x] == '1')
			render->hit = 1;
	}
}

static inline void	ft_steps(t_game *game, t_render *render)
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

static inline void	ft_rays(t_game *game, t_render *render, int x)
{
	render->camera_x = 2.0 * x / ((double)WIDTH) - 1.0;
	render->ray_dir = (t_vec){game->p.dir.x + game->p.plane.x
		* render->camera_x, game->p.dir.y + game->p.plane.y * render->camera_x};
	render->map = (t_intvec){game->p.pos.x, game->p.pos.y};
	render->delta_dist = (t_vec){1e30, 1e30};
	if (render->ray_dir.x)
		render->delta_dist.x = fabs(1.0 / render->ray_dir.x);
	if (render->ray_dir.y)
		render->delta_dist.y = fabs(1.0 / render->ray_dir.y);
	render->hit = 0;
	ft_steps(game, render);
	ft_dda(game, render);
	if (render->side > 0)
		render->perp_dist = render->side_dist.y - render->delta_dist.y;
	else
		render->perp_dist = render->side_dist.x - render->delta_dist.x;
	render->line_height = (int)(HEIGHT / render->perp_dist);
	render->draw.x = -render->line_height / 2 + HALF_HEIGHT + game->p.y;
	if (render->draw.x < 0)
		render->draw.x = 0;
	render->draw.y = render->line_height / 2 + HALF_HEIGHT + game->p.y;
	if (render->draw.y >= HEIGHT)
		render->draw.y = HEIGHT - 1;
}

inline void	ft_draw(t_game *game)
{
	int			y;
	int			x;
	
	x = -1;
	while (++x < WIDTH)
	{
		ft_rays(game, &game->r, x);
		ft_wall(game);
		game->r.zbuffer[x] = game->r.perp_dist;
		y = -1;
		while (++y < HEIGHT)
		{
			if (y < game->r.draw.x)
				my_mlx_pixel_put(&game->screen, x, y, game->map.c_color);
			else if (y >= game->r.draw.x && y <= game->r.draw.y)
				ft_drawpixel(game, x, y);
			else
				my_mlx_pixel_put(&game->screen, x, y, game->map.f_color);
		}
	}
	ft_drawsprites(game);
	ft_drawmap(game, x, y);
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.win, game->screen.img, 0,
		0);
}
