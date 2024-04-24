/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 16:40:39 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/24 21:21:53 by ybelatar         ###   ########.fr       */
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

	ft_import_portals(g, pt);
	ft_import_glass(g, gt);
	ft_import_sprites(g);
	if (ft_check_walls(g) || ft_check_sprites(g))
		return (ft_dprintf(2, ERR_FORMAT, NAME, TEXTURE_SIZE), 1);
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
