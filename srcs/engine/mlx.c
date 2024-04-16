/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:40:39 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/16 02:55:12 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_import_textures(t_game *g)
{
	int	exit;
	int	i;

	g->s.a = mlx_get_data_addr(g->s.img, &g->s.bpp, &g->s.ll, &g->s.endian);
	i = WTEXTURES;
	exit = 0;
	while (i--)
	{
		if (!g->wt[i].img)
			exit = 1;
		else
			g->wt[i].a = mlx_get_data_addr(g->wt[i].img, &g->wt[i].bpp,
					&g->wt[i].ll, &g->wt[i].endian);
	}
	i = WTEXTURES;
	while (exit && i--)
		if (g->wt[i].img)
			mlx_destroy_image(g->mlx.mlx, g->wt[i].img);
	if (exit)
		return (mlx_destroy_image(g->mlx.mlx, g->s.img),
			mlx_destroy_window(g->mlx.mlx, g->mlx.win),
			mlx_destroy_display(g->mlx.mlx), free(g->mlx.mlx), 1);
	return (0);
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
	{
		g->wt[i].img = mlx_xpm_file_to_image(g->mlx.mlx, g->files[i],
				&g->wt[i].width, &g->wt[i].height);
	}
	if (ft_import_textures(g))
		return (ft_dprintf(STDERR_FILENO, ERR_FORMAT, NAME, IMPORT_ERR), 1);
	return (0);
}

int	ft_check_textures(t_game *game)
{
	int	i;
	int	err;

	err = 0;
	i = WTEXTURES;
	while (i--)
	{
		if (!game->wt[i].width || game->wt[i].height % game->wt[i].width)
			err = 1;
		game->wt[i].frames = game->wt[i].height / game->wt[i].width;
	}
	i = STEXTURES;
	while (i--)
	{
		if (!game->st[i].a)
			continue ;
		if (!game->st[i].width || game->st[i].height % game->st[i].width)
			return (1);
		game->st[i].frames = game->st[i].height / game->st[i].width;
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
	g->ptextures[0].img = mlx_xpm_file_to_image(g->mlx.mlx,
			"assets/textures/walls/blue.xpm", &g->ptextures[0].width,
			&g->ptextures[0].height);
	g->ptextures[0].a = mlx_get_data_addr(g->ptextures[0].img,
			&g->ptextures[0].bpp, &g->ptextures[0].ll, &g->ptextures[0].endian);
	g->ptextures[1].img = mlx_xpm_file_to_image(g->mlx.mlx,
			"assets/textures/walls/orange.xpm", &g->ptextures[1].width,
			&g->ptextures[1].height);
	g->ptextures[1].a = mlx_get_data_addr(g->ptextures[1].img,
			&g->ptextures[1].bpp, &g->ptextures[1].ll, &g->ptextures[1].endian);
	g->ptextures[2].img = mlx_xpm_file_to_image(g->mlx.mlx,
			"assets/textures/walls/blue.xpm", &g->ptextures[2].width,
			&g->ptextures[2].height);
	g->ptextures[2].a = mlx_get_data_addr(g->ptextures[2].img,
			&g->ptextures[2].bpp, &g->ptextures[2].ll, &g->ptextures[2].endian);
	g->ptextures[3].img = mlx_xpm_file_to_image(g->mlx.mlx,
			"assets/textures/walls/orange.xpm", &g->ptextures[3].width,
			&g->ptextures[3].height);
	g->ptextures[3].a = mlx_get_data_addr(g->ptextures[3].img,
			&g->ptextures[3].bpp, &g->ptextures[3].ll, &g->ptextures[3].endian);
	mlx_loop(g->mlx.mlx);
}
