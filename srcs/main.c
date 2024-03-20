/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:45:59 by ybelatar          #+#    #+#             */
/*   Updated: 2024/03/20 02:35:52 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_loop(void *param)
{
	t_game	*game;
	double	x;
	double	y;

	game = param;
	game->now = clock();
	if (game->now - game->last < 12000)
		return (0);
	game->last = clock();
	if (game->front)
	{
		if (game->map.map[(int)(game->p.pos.y
				+ game->p.dir.y * game->p.speed)][(int)game->p.pos.x] == '0')
			game->p.pos.y += game->p.dir.y * game->p.speed;
		if (game->map.map[(int)game->p.pos.y][(int)(game->p.pos.x
				+ game->p.dir.x * game->p.speed)] == '0')
			game->p.pos.x += game->p.dir.x * game->p.speed;
	}
	if (game->back)
	{
		if (game->map.map[(int)(game->p.pos.y
				- game->p.dir.y * game->p.speed)][(int)game->p.pos.x] == '0')
			game->p.pos.y -= game->p.dir.y * game->p.speed;
		if (game->map.map[(int)game->p.pos.y][(int)(game->p.pos.x
				- game->p.dir.x * game->p.speed)] == '0')
			game->p.pos.x -= game->p.dir.x * game->p.speed;
	}
	if (game->right)
	{
		x = game->p.dir.x;
		y = game->p.dir.y;
		game->p.dir.x = x * cos(-0.1) - y * sin(-0.1);
		game->p.dir.y = x * sin(-0.1) + y * cos(-0.1);
		x = game->p.plane.x;
		y = game->p.plane.y;
		game->p.plane.x = x * cos(-0.1) - y * sin(-0.1);
		game->p.plane.y = x * sin(-0.1) + y * cos(-0.1);
	}
	if (game->left)
	{
		x = game->p.dir.x;
		y = game->p.dir.y;
		game->p.dir.x = x * cos(0.1) - y * sin(0.1);
		game->p.dir.y = x * sin(0.1) + y * cos(0.1);
		x = game->p.plane.x;
		y = game->p.plane.y;
		game->p.plane.x = x * cos(0.1) - y * sin(0.1);
		game->p.plane.y = x * sin(0.1) + y * cos(0.1);
	}
	if (game->up)
	{
		if (game->p.y < HEIGHT)
			game->p.y += 20;
	}
	if (game->down)
		if (game->p.y > -HEIGHT)
			game->p.y -= 20;
	ft_draw(game);
	return (0);
}

static inline int	ft_import_textures(t_game *g)
{
	int	exit;
	int	i;

	g->screen.addr = mlx_get_data_addr(g->screen.img, &g->screen.bpp,
			&g->screen.ll, &g->screen.endian);
	i = TEXTURES;
	exit = 0;
	while (i--)
	{
		if (!g->textures[i].img)
			exit = 1;
		else
			g->textures[i].addr = mlx_get_data_addr(g->textures[i].img,
					&g->textures[i].bpp, &g->textures[i].ll,
					&g->textures[i].endian);
	}
	i = TEXTURES;
	while (exit && i--)
		if (g->textures[i].img)
			mlx_destroy_image(g->mlx.mlx, g->textures[i].img);
	if (exit)
		return (mlx_destroy_image(g->mlx.mlx, g->screen.img),
			mlx_destroy_window(g->mlx.mlx, g->mlx.win),
			mlx_destroy_display(g->mlx.mlx), free(g->mlx.mlx), 1);
	return (0);
}

static inline int	ft_init_mlx(t_game *g)
{
	int	i;

	g->mlx.mlx = mlx_init();
	if (!g->mlx.mlx)
		return (ft_dprintf(STDERR_FILENO, ERR_FORMAT, NAME, MLX_ERR), 1);
	g->mlx.win = mlx_new_window(g->mlx.mlx, WIDTH, HEIGHT, NAME);
	if (!g->mlx.win)
		return (ft_dprintf(2, ERR_FORMAT, NAME, WIN_ERR), free(g->mlx.mlx), 1);
	g->screen.img = mlx_new_image(g->mlx.mlx, WIDTH, HEIGHT);
	if (!g->screen.img)
		return (ft_dprintf(STDERR_FILENO, ERR_FORMAT, NAME, SCREEN_ERR),
			mlx_destroy_window(g->mlx.mlx, g->mlx.win),
			mlx_destroy_display(g->mlx.mlx), free(g->mlx.mlx), 1);
	i = 0;
	while (i < TEXTURES)
	{
		g->textures[i].img = mlx_xpm_file_to_image(g->mlx.mlx, g->files[i],
				&g->textures[i].width, &g->textures[i].height);
		++i;
	}
	if (ft_import_textures(g))
		return (ft_dprintf(STDERR_FILENO, ERR_FORMAT, NAME, IMPORT_ERR), 1);
	return (mlx_hook(g->mlx.win, ON_KEYPRESS, KEYPRESS_MASK, on_key_press, g),
		mlx_hook(g->mlx.win, ON_DESTROY, NO_MASK, on_destroy_event, g),
		mlx_loop_hook(g->mlx.mlx, ft_loop, g), mlx_hook(g->mlx.win,
			ON_KEYRELEASE, KEYRELEASE_MASK, on_key_release, g), 0);
}

static inline void	ft_start(t_game *game)
{
	int	i;
	int	err;

	i = TEXTURES;
	err = 0;
	while (i--)
		if (!game->textures[i].width || game->textures[i].height
			% game->textures[i].width)
			err = 1;
	if (!err)
	{
		ft_draw(game);
		mlx_loop(game->mlx.mlx);
	}
	else
		ft_dprintf(2, ERR_FORMAT, NAME, TEXTURE_SIZE);
	mlx_destroy_image(game->mlx.mlx, game->screen.img);
	i = 0;
	while (i < TEXTURES)
		mlx_destroy_image(game->mlx.mlx, game->textures[i++].img);
	mlx_destroy_window(game->mlx.mlx, game->mlx.win);
	mlx_destroy_display(game->mlx.mlx);
	free(game->mlx.mlx);
	gc(0, 0);
}

int	main(int ac, char **av)
{
	static t_game	game = {0};
	const char		*s;

	if (ac != 2)
		return (ft_dprintf(STDERR_FILENO, ERR_FORMAT, NAME, ARGS_ERR), 1);
	s = ft_strchr(av[1], '.');
	if (!s)
		return (ft_dprintf(STDERR_FILENO, ERR_FORMAT, NAME, EXT_ERR), 2);
	if (ft_strcmp(s, EXT))
		return (ft_dprintf(STDERR_FILENO, ERR_FORMAT, NAME, EXT_ERR), 2);
	init_map(av[1], &game);
	if (ft_init_mlx(&game))
		return (gc(NULL, 0), 3);
	ft_start(&game);
	return (0);
}
