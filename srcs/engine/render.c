/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 16:55:26 by wouhliss          #+#    #+#             */
/*   Updated: 2024/03/20 23:41:00 by wouhliss         ###   ########.fr       */
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
		if (game->map.map[render->map.y][render->map.x] != '0')
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
	render->draw.x = -render->line_height / 2 + HEIGHT / 2 + game->p.y;
	if (render->draw.x < 0)
		render->draw.x = 0;
	render->draw.y = render->line_height / 2 + HEIGHT / 2 + game->p.y;
	if (render->draw.y >= HEIGHT)
		render->draw.y = HEIGHT - 1;
	switch (render->side)
	{
	case -1:
		render->color = create_trgb(0, 128, 0, 0);
		break ;
	case -2:
		render->color = create_trgb(0, 0, 128, 0);
		break ;
	case 1:
		render->color = create_trgb(0, 0, 0, 128);
		break ;
	default:
		render->color = create_trgb(0, 128, 0, 128);
		break ;
	}
}

inline void	ft_draw(t_game *game)
{
	t_render	render;
	int			y;
	int			x;
	int			map_x;
	int			map_y;

	x = 0;
	while (x < WIDTH)
	{
		ft_rays(game, &render, x);
		y = 0;
		while (y < HEIGHT)
		{
			if (y < render.draw.x)
				my_mlx_pixel_put(&game->screen, x, y, game->map.c_color);
			else if (y >= render.draw.x && y <= render.draw.y)
				my_mlx_pixel_put(&game->screen, x, y, render.color);
			else
				my_mlx_pixel_put(&game->screen, x, y, game->map.f_color);
			++y;
		}
		++x;
	}
	map_x = (int)game->p.pos.x - 10;
	if (map_x < 0)
		map_x = 0;
	map_y = (int)game->p.pos.y - 10;
	if (map_y < 0)
		map_y = 0;
	x = 50;
	while (x < MINIMAP_WIDTH + 50)
	{
		y = 20;
		while (y < MINIMAP_HEIGHT + 20)
		{
			if (map_x + ((x - 50) / 16) >= game->width || map_y + ((y - 20) / 16) >= game->length)
				;
			else if (game->map.map[map_y + ((y - 20) / 16)][map_x + ((x - 50) / 16)] == '1')
				my_mlx_pixel_put(&game->screen, x, y, 0x00000000);
			else if (game->map.map[map_y + ((y - 20) / 16)][map_x + ((x - 50) / 16)] == '0')
				my_mlx_pixel_put(&game->screen, x, y, 0x00FFFFFF);
			if ((int)game->p.pos.x == map_x + ((x - 50) / 16) && (int)game->p.pos.y == map_y + ((y - 20) / 16))
				my_mlx_pixel_put(&game->screen, x, y, 0x00FF0000);
			++y;
		}
		++x;
	}
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.win, game->screen.img, 0,
		0);
}
