/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/17 16:55:26 by wouhliss          #+#    #+#             */
/*   Updated: 2024/03/22 02:45:25 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// void	draw_rayons_all_2(t_map *map, t_drawrays *r, t_plane *p, int i)
// {
// 	int	y;

// 	y = -1;
// 	r->step = 1.0 * 64 / r->lineh;
// 	r->texpos = (r->draw.x - HEIGHT / 2 + r->lineh / 2) * r->step;
// 	while (++y < HEIGHT)
// 	{
// 		if (y < r->draw.x)
// 			r->color = create_trgb(map->ceiling);
// 		else if (y > r->draw.y)
// 			r->color = create_trgb(map->floor);
// 		else
// 		{
// 			r->tex.y = (int)r->texpos & (64 - 1);
// 			r->color = map->plane->texture[r->texnum][64 * r->tex.y + r->tex.x];
// 			r->texpos += r->step;
// 			wall_color(map->plane, &r->color, r->tex);
// 		}
// 		map->plane->buff[y][(int)i] = r->color;
// 		p->re_buf = 1;
// 	}
// }

static inline double	get_wall_x(t_game *g, t_render *r, double pwall)
{
	double	wallx;

	if (r->side == 0)
		wallx = g->p.pos.y + pwall * r->ray_dir.y;
	else
		wallx = g->p.pos.x + pwall * r->ray_dir.x;
	wallx -= floor(wallx);
	return (wallx);
}

static inline int	get_tex_x(t_render *r, double wallx)
{
	int	val;

	val = (int)(wallx * (double)(64));
	if (r->side == 0 && r->ray_dir.x > 0)
		val = 64 - val - 1;
	if (r->side == 1 && r->ray_dir.y > 0)
		val = 64 - val - 1;
	return (val);
}
// static inline void	ft_textures(t_game *game, t_render *render, int x, int y, int s, int texpos, int texx)
// {
// 	(void)game, (void)render, (void)x, (void)y;
// 	t_intvec tex;
// 	tex.y = (int)texpos & (64 - 1);
// 	int color = game->textures[0].addr[64 * tex.y + texx];
// 	texpos += s;
// 	my_mlx_pixel_put(&game->screen, x, y, color);
// 	// ou ton mur tape
// 	// 
// }

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
			render->side = 0;
			// if (render->step.x < 0)
				// render->side = -2;
		}
		else
		{
			render->side_dist.y += render->delta_dist.y;
			render->map.y += render->step.y;
			render->side = 1;
			// if (render->step.y < 0)
				// render->side = 2;
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
	// switch (render->side)
	// {
	// case -1:
	// 	render->color = create_trgb(0, 128, 0, 0); //east
	// 	break ;
	// case -2:
	// 	render->color = create_trgb(0, 0, 128, 0); //west
	// 	break ;
	// case 1:
	// 	render->color = create_trgb(0, 0, 0, 128); //south
	// 	break ;
	// default:
	// 	render->color = create_trgb(0, 128, 0, 128); //north
	// 	break ;
	// }
}
// static inline double	sides(t_game *g, t_render *r)
// {
// 	double	pwall;

// 	if (r->side == 0)
// 		pwall = (r->map.x - g->p.pos.x + (1 - r->step.x) / 2) / r->ray_dir.x;
// 	else
// 		pwall = (r->map.y - g->p.pos.y + (1 - r->step.y) / 2) / r->ray_dir.y;
// 	return (pwall);
// }
inline void	ft_draw(t_game *game)
{
	t_render	render;
	int			y;
	int			x;
	int			map_x;
	t_intvec tex;
	int			map_y;

	x = 0;
	while (x < WIDTH)
	{
		ft_rays(game, &render, x);
		y = 0;
		
		// moha
		// double pwall = sides(game ,&render);
		double wallx = get_wall_x(game, &render, render.perp_dist);
		tex.x = get_tex_x(&render, wallx);
		
		double mystep = 1.0 * 64 / render.line_height;
		double texpos = (render.draw.x - HEIGHT / 2 + render.line_height / 2) * mystep;
		while (y < HEIGHT)	
		{
			if (y < render.draw.x)
				my_mlx_pixel_put(&game->screen, x, y, game->map.c_color);
			else if (y >= render.draw.x && y <= render.draw.y)
			{
				tex.y = (int)texpos & (64 - 1);
				texpos += mystep;
				int color = ((int *)game->textures[3].addr)[64 * tex.y + tex.x];
				//printf("[%i|%i]%i %i %f %f {%f} %f {%f, %f} %i\n",x,y, tex.x, tex.y, texpos, mystep, wallx, render.perp_dist, render.ray_dir.x, render.ray_dir.y, color);	
				my_mlx_pixel_put(&game->screen, x, y, color);
				
				// ft_textures(game, &render, x, y, mystep, texpos, texx);

			}
			else
				my_mlx_pixel_put(&game->screen, x, y, game->map.f_color);
			++y;
		}
		++x;
	}
	//exit(0);
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
