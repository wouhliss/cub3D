/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:36:48 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/03 10:57:11 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static inline double	get_wall_x(t_render *r)
{
	double	wallx;

	if (r->side < 0)
		wallx = r->pos.y + r->perp_dist * r->ray_dir.y;
	else
		wallx = r->pos.x + r->perp_dist * r->ray_dir.x;
	wallx -= floor(wallx);
	return (wallx);
}

static inline int	get_tex_x(t_render *r, const double wallx)
{
	int	val;

	val = (wallx * r->twidth);
	if (r->side < 0 && r->ray_dir.x > 0)
		val = r->twidth - val - 1;
	if (r->side > 1 && r->ray_dir.y > 0)
		val = r->twidth - val - 1;
	return (val);
}

inline void	ft_wall(const t_game *game, t_render *r)
{
	double	wallx;

	if (r->side == -1)
		r->id = 3;
	else if (r->side == -2)
		r->id = 2;
	else if (r->side == 1)
		r->id = 1;
	else if (r->side == 2)
		r->id = 0;
	r->twidth = game->textures[r->id].width;
	r->s = game->textures[r->id].s;
	wallx = get_wall_x(r);
	r->tex.x = get_tex_x(r, wallx);
	r->mystep = (double)r->twidth / r->line_height;
	r->texpos = (r->draw.x - HALF_HEIGHT + r->line_height / 2 - game->p.y
			- (int)(game->p.jump) / r->perp_dist) * r->mystep;
}

static inline double	get_dwall_x(t_render *r)
{
	double	wallx;

	if (r->dside < 0)
		wallx = r->pos.y + r->dperp_dist * r->ray_dir.y;
	else
		wallx = r->pos.x + r->dperp_dist * r->ray_dir.x;
	wallx -= floor(wallx);
	return (wallx);
}

static inline int	get_dtex_x(t_render *r, const double wallx)
{
	int	val;

	val = (wallx * r->dtwidth);
	if (r->dside < 0 && r->ray_dir.x > 0)
		val = r->dtwidth - val - 1;
	if (r->dside > 1 && r->ray_dir.y > 0)
		val = r->dtwidth - val - 1;
	return (val);
}

inline void	ft_dwall(const t_game *game, t_render *r)
{
	double	wallx;

	r->did = 4;
	r->dtwidth = game->textures[r->did].width;
	r->ds = game->textures[r->did].s;
	wallx = get_dwall_x(r);
	r->dtex.x = get_dtex_x(r, wallx);
	r->dmystep = (double)r->dtwidth / r->dline_height;
	r->dtexpos = (r->ddraw.x - HALF_HEIGHT + r->dline_height / 2 - game->p.y
			- (int)(game->p.jump) / r->dperp_dist) * r->dmystep;
}

inline void	ft_ddrawpixel(t_game *game, const int x, const int y, t_render *r)
{
	int	color;

	r->dtex.y = (int)r->dtexpos & (r->dtwidth - 1);
	r->dtexpos += r->dmystep;
	color = ((int *)game->textures[r->did].addr)[r->ds + r->dtwidth * r->dtex.y
		+ (int)(r->dtex.x - r->dtex.x * r->door->frame)];
	if (game->p.looking && game->p.look_pos.x == r->door->pos.x
		&& game->p.look_pos.y == r->door->pos.y && (!r->dtex.y || r->dtex.y == r->dtwidth
			- 1 || !r->dtex.x || r->dtex.x == r->dtwidth - 1))
		color = 0x00FF0000;
	if ((color & 0x00FFFFFF) != 0)
	{
		game->zbuffer[x][y] = r->dperp_dist;
		my_mlx_pixel_put(&game->screen, x, y, color);
	}
}


static inline double	get_pwall_x(t_render *r)
{
	double	wallx;

	if (r->pside < 0)
		wallx = r->pos.y + r->pperp_dist * r->ray_dir.y;
	else
		wallx = r->pos.x + r->pperp_dist * r->ray_dir.x;
	wallx -= floor(wallx);
	return (wallx);
}

static inline int	get_ptex_x(t_render *r, const double wallx)
{
	int	val;

	val = (wallx * r->ptwidth);
	if (r->pside < 0 && r->ray_dir.x > 0)
		val = r->ptwidth - val - 1;
	if (r->pside > 1 && r->ray_dir.y > 0)
		val = r->ptwidth - val - 1;
	return (val);
}

static inline int	get_pwtex_x(t_render *r, const double wallx)
{
	int	val;

	val = (wallx * r->ptwidth);
	if (r->pside < 0 && r->ray_dir.x > 0)
		val = r->pwtwidth - val - 1;
	if (r->pside > 1 && r->ray_dir.y > 0)
		val = r->pwtwidth - val - 1;
	return (val);
}

inline void	ft_pwall(const t_game *game, t_render *r)
{
	double	wallx;

	if (r->phit == 3)
		r->pid = 9;
	else if (r->phit == 4)
		r->pid = 10;
	if (r->pside == -1)
		r->pwid = 3;
	else if (r->pside == -2)
		r->pwid = 2;
	else if (r->pside == 1)
		r->pwid = 1;
	else if (r->pside == 2)
		r->pwid = 0;
	r->ptwidth = game->textures[r->pid].width;
	r->ps = game->textures[r->pid].s;
	r->pwtwidth = game->textures[r->pwid].width;
	r->pws = game->textures[r->pwid].s;
	wallx = get_pwall_x(r);
	r->ptex.x = get_ptex_x(r, wallx);
	r->pwtex.x = get_pwtex_x(r, wallx);
	r->pmystep = (double)r->ptwidth / r->pline_height;
	r->ptexpos = (r->pdraw.x - HALF_HEIGHT + r->pline_height / 2 - game->p.y
			- (int)(game->p.jump) / r->pperp_dist) * r->pmystep;
	r->pwmystep = (double)r->pwtwidth / r->pline_height;
	r->pwtexpos = (r->pdraw.x - HALF_HEIGHT + r->pline_height / 2 - game->p.y
			- (int)(game->p.jump) / r->pperp_dist) * r->pwmystep;
}

void	ft_pdrawpixel(t_game *game, const int x, const int y, t_render *r)
{
	int	pcolor;
	int	color;

	r->ptex.y = (int)r->ptexpos & (r->ptwidth - 1);
	r->ptexpos += r->pmystep;
	pcolor = ((int *)game->textures[r->pid].addr)[r->ps + r->ptwidth * r->ptex.y
		+ r->ptex.x];
	r->pwtex.y = (int)r->pwtexpos & (r->pwtwidth - 1);
	r->pwtexpos += r->pwmystep;
	color = ((int *)game->textures[r->pwid].addr)[r->pws + r->pwtwidth * r->pwtex.y
		+ r->pwtex.x];
	if ((pcolor & 0x00FFFFFF) != 0)
	{
		game->zbuffer[x][y] = r->pperp_dist;
		my_mlx_pixel_put(&game->screen, x, y, pcolor);
	}
	if (pcolor == 65280)
	{
		game->zbuffer[x][y] = r->pperp_dist;
		my_mlx_pixel_put(&game->screen, x, y, color);
	}
}

inline void	ft_drawpixel(const t_game *game, const int x, const int y,
		t_render *r)
{
	int	color;

	r->tex.y = (int)r->texpos & (r->twidth - 1);
	r->texpos += r->mystep;
	color = ((int *)game->textures[r->id].addr)[r->s + r->twidth * r->tex.y
		+ r->tex.x];
	if (game->p.looking && game->p.look_pos.x == r->map.x
		&& game->p.look_pos.y == r->map.y && (!r->tex.y || r->tex.y == r->twidth
			- 1 || !r->tex.x || r->tex.x == r->twidth - 1))
		color = 0x00FF0000;
	my_mlx_pixel_put(&game->screen, x, y, color);
}
