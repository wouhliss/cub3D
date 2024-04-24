/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:40:39 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/24 19:18:44 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_import_textures(t_game *g)
{
	int	i;

	g->s.a = mlx_get_data_addr(g->s.img, &g->s.bpp, &g->s.ll, &g->s.endian);
	i = WTEXTURES;
	while (i--)
	{
		if (!g->wt[i].img)
		{
			g->wt[i] = g->dfl;
			g->wt[i].img = 0;
		}
		else
			g->wt[i].a = mlx_get_data_addr(g->wt[i].img, &g->wt[i].bpp,
					&g->wt[i].ll, &g->wt[i].endian);
	}
}

int	ft_init_mlx(t_game *g)
{
	int	i;

	g->mlx.mlx = mlx_init();
	if (!g->mlx.mlx)
		return (ft_dprintf(STDERR_FILENO, ERR_FORMAT, NAME, MLX_ERR), 1);
	g->mlx.win = mlx_new_window(g->mlx.mlx, W, HEIGHT, NAME);
	if (!g->mlx.win)
		return (ft_dprintf(2, ERR_FORMAT, NAME, WIN_ERR), free(g->mlx.mlx), 1);
	g->s.img = mlx_new_image(g->mlx.mlx, W, HEIGHT);
	if (!g->s.img)
		return (ft_dprintf(STDERR_FILENO, ERR_FORMAT, NAME, SCREEN_ERR),
			mlx_destroy_window(g->mlx.mlx, g->mlx.win),
			mlx_destroy_display(g->mlx.mlx), free(g->mlx.mlx), 1);
	i = -1;
	while (++i < WTEXTURES)
		if (g->files[i])
			g->wt[i].img = mlx_xpm_file_to_image(g->mlx.mlx, g->files[i],
					&g->wt[i].w, &g->wt[i].height);
	ft_import_textures(g);
	return (0);
}

int	ft_check_textures(t_game *g)
{
	const char	*gt[] = {"glass.xpm", "black_stained_glass.xpm",
		"blue_stained_glass.xpm", "brown_stained_glass.xpm",
		"cyan_stained_glass.xpm", "gray_stained_glass.xpm",
		"green_stained_glass.xpm", "light_blue_stained_glass.xpm",
		"lime_stained_glass.xpm", "magenta_stained_glass.xpm",
		"pink_stained_glass.xpm", "purple_stained_glass.xpm",
		"red_stained_glass.xpm", "light_gray_stained_glass.xpm",
		"white_stained_glass.xpm", "yellow_stained_glass.xpm",
		"tinted_stained_glass.xpm", "orange_stained_glass.xpm", 0};
	const char	*pt[] = {"blue_closed.xpm", "orange_closed.xpm", "blue.xpm",
		"orange.xpm", 0};
	int			i;
	int			err;

	i = -1;
	while (pt[++i])
	{
		g->pt[i].img = mlx_xpm_file_to_image(g->mlx.mlx,
				(char *)gc(ft_mprintf("%s%s", "assets/textures/walls/", pt[i]),
					ADD), &g->pt[i].w, &g->pt[i].height);
		if (!g->pt[i].img)
		{
			g->pt[i] = g->dfl;
			g->pt[i].img = 0;
		}
		else
			g->pt[i].a = mlx_get_data_addr(g->pt[i].img, &g->pt[i].bpp,
					&g->pt[i].ll, &g->pt[i].endian);
	}
	i = -1;
	while (gt[++i])
	{
		g->gt[i].img = mlx_xpm_file_to_image(g->mlx.mlx,
				(char *)gc(ft_mprintf("%s%s", "assets/textures/walls/", gt[i]),
					ADD), &g->gt[i].w, &g->gt[i].height);
		if (!g->gt[i].img)
		{
			g->gt[i] = g->dfl;
			g->gt[i].img = 0;
		}
		else
			g->gt[i].a = mlx_get_data_addr(g->gt[i].img, &g->gt[i].bpp,
					&g->gt[i].ll, &g->gt[i].endian);
	}
	i = -1;
	while (++i < STEXTURES)
	{
		if (g->sfiles[i])
			g->st[i].img = mlx_xpm_file_to_image(g->mlx.mlx, g->sfiles[i],
					&g->st[i].w, &g->st[i].height);
		if (!g->st[i].img)
		{
			g->st[i] = g->dfl;
			g->st[i].img = 0;
		}
		else
			g->st[i].a = mlx_get_data_addr(g->st[i].img, &g->st[i].bpp,
					&g->st[i].ll, &g->st[i].endian);
	}
	err = 0;
	i = WTEXTURES;
	while (i--)
	{
		if (!g->wt[i].w || g->wt[i].height % g->wt[i].w)
			err = 1;
		else
			g->wt[i].frames = g->wt[i].height / g->wt[i].w;
	}
	i = STEXTURES;
	while (i--)
	{
		if (!g->st[i].a)
			continue ;
		if (!g->st[i].w || g->st[i].height % g->st[i].w)
			return (1);
		g->st[i].frames = g->st[i].height / g->st[i].w;
	}
	if (err)
		return (ft_dprintf(2, ERR_FORMAT, NAME, TEXTURE_SIZE), err);
	return (0);
}

void	ft_start(t_game *g)
{
	if (ft_check_textures(g))
		return ;
	mlx_hook(g->mlx.win, ON_KEYDOWN, KEYPRESS_MASK, on_key_press, g);
	mlx_hook(g->mlx.win, ON_DESTROY, NO_MASK, on_destroy_event, g);
	mlx_hook(g->mlx.win, ON_MOUSEMOVE, POINTERMOTION_MASK, on_mouse_move, g);
	mlx_hook(g->mlx.win, ON_MOUSEDOWN, BUTTONPRESS_MASK, on_mouse_click, g);
	mlx_loop_hook(g->mlx.mlx, ft_loop, g);
	mlx_hook(g->mlx.win, ON_KEYUP, KEYRELEASE_MASK, on_key_release, g);
	mlx_loop(g->mlx.mlx);
}
