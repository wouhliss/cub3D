/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:45:59 by ybelatar          #+#    #+#             */
/*   Updated: 2024/03/27 15:59:55 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static inline void	ft_handleinput(t_game *game, double delta)
{
	double	x;
	double	speed;
	double	sens;

	speed = (delta * 0.00001);
	sens = 0.000005 * delta;
	if (game->front)
	{
		game->p.speed.y += game->p.dir.y * speed;
		if (game->p.speed.y > 0.2)
			game->p.speed.y = 0.2;
		else if (game->p.speed.y < -0.2)
			game->p.speed.y = -0.2;
		game->p.speed.x += game->p.dir.x * speed;
		if (game->p.speed.x > 0.2)
			game->p.speed.x = 0.2;
		else if (game->p.speed.x < -0.2)
			game->p.speed.x = -0.2;
	}
	if (game->back)
	{
		game->p.speed.y -= game->p.dir.y * speed;
		if (game->p.speed.y > 0.2)
			game->p.speed.y = 0.2;
		else if (game->p.speed.y < -0.2)
			game->p.speed.y = -0.2;
		game->p.speed.x -= game->p.dir.x * speed;
		if (game->p.speed.x > 0.2)
			game->p.speed.x = 0.2;
		else if (game->p.speed.x < -0.2)
			game->p.speed.x = -0.2;
	}
	if (game->left)
	{
		game->p.speed.x += -game->p.dir.y * speed;
		if (game->p.speed.x > 0.2)
			game->p.speed.x = 0.2;
		else if (game->p.speed.x < -0.2)
			game->p.speed.x = -0.2;
		game->p.speed.y += game->p.dir.x * speed;
		if (game->p.speed.y > 0.2)
			game->p.speed.y = 0.2;
		else if (game->p.speed.y < -0.2)
			game->p.speed.y = -0.2;
	}
	if (game->right)
	{
		game->p.speed.x -= -game->p.dir.y * speed;
		if (game->p.speed.x > 0.2)
			game->p.speed.x = 0.2;
		else if (game->p.speed.x < -0.2)
			game->p.speed.x = -0.2;
		game->p.speed.y -= game->p.dir.x * speed;
		if (game->p.speed.y > 0.2)
			game->p.speed.y = 0.2;
		else if (game->p.speed.y < -0.2)
			game->p.speed.y = -0.2;
	}
	if (game->turn_r)
	{
		x = game->p.dir.x;
		game->p.dir.x = x * cos(-(sens)) - game->p.dir.y * sin(-(sens));
		game->p.dir.y = x * sin(-(sens)) + game->p.dir.y * cos(-(sens));
		x = game->p.plane.x;
		game->p.plane.x = x * cos(-(sens)) - game->p.plane.y * sin(-(sens));
		game->p.plane.y = x * sin(-(sens)) + game->p.plane.y * cos(-(sens));
	}
	if (game->turn_l)
	{
		x = game->p.dir.x;
		game->p.dir.x = x * cos((sens)) - game->p.dir.y * sin((sens));
		game->p.dir.y = x * sin((sens)) + game->p.dir.y * cos((sens));
		x = game->p.plane.x;
		game->p.plane.x = x * cos((sens)) - game->p.plane.y * sin((sens));
		game->p.plane.y = x * sin((sens)) + game->p.plane.y * cos((sens));
	}
	if (game->up)
		game->p.y += (0.002 * delta);
	if (game->down)
		game->p.y -= (0.002 * delta);
}

int	ft_loop(void *param)
{
	t_game	*game;
	double	delta;

	game = param;
	game->last = game->now;
	game->now = clock();
	delta = game->now - game->last;
	if (game->p.pos.y + (game->p.speed.y * delta * 0.00001) > 0 && game->p.pos.y
		+ (game->p.speed.y * delta * 0.00001) < game->length
		&& game->map.map[(int)(game->p.pos.y + (game->p.speed.y * delta
				* 0.00001))][(int)game->p.pos.x] == '0')
		game->p.pos.y += game->p.speed.y * delta * 0.00001;
	else
		game->p.speed.y = 0;
	if (game->p.pos.x + (game->p.speed.x * delta * 0.00001) > 0 && game->p.pos.x
		+ (game->p.speed.x * delta * 0.00001) < game->width
		&& game->map.map[(int)game->p.pos.y][(int)(game->p.pos.x
			+ (game->p.speed.x * delta * 0.00001))] == '0')
		game->p.pos.x += game->p.speed.x * delta * 0.00001;
	else
		game->p.speed.x = 0;
	ft_handleinput(game, delta);
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
	i = -1;
	while (++i < TEXTURES)
		g->textures[i].img = mlx_xpm_file_to_image(g->mlx.mlx, g->files[i],
				&g->textures[i].width, &g->textures[i].height);
	if (ft_import_textures(g))
		return (ft_dprintf(STDERR_FILENO, ERR_FORMAT, NAME, IMPORT_ERR), 1);
	return (mlx_hook(g->mlx.win, ON_KEYPRESS, KEYPRESS_MASK, on_key_press, g),
		mlx_hook(g->mlx.win, ON_DESTROY, NO_MASK, on_destroy_event, g),
		mlx_hook(g->mlx.win, ON_MOUSEMOVE, POINTERMOTION_MASK, on_mouse, g),
		mlx_loop_hook(g->mlx.mlx, ft_loop, g), mlx_hook(g->mlx.win,
			ON_KEYRELEASE, KEYRELEASE_MASK, on_key_release, g), 0);
}

static inline void	ft_getsprites(t_game *game)
{
	int	x;
	int	y;
	int	i;

	i = 0;
	x = 0;
	while (x < game->width)
	{
		y = 0;
		while (y < game->length)
		{
			if (game->map.map[y][x] == 'P')
			{
				game->sprites[i].type = 0;
				game->sprites[i].vdiff = 128.0;
				game->sprites[i].hr = 2;
				game->sprites[i].vr = 2;
				game->sprites[i++].pos = (t_vec){x + 0.5, y + 0.5};
				game->map.map[y][x] = '0';	
			}
			++y;
		}
		++x;
	}
}

static inline void	ft_start(t_game *game, int *err)
{
	int	i;

	i = TEXTURES;
	while (i--)
		if (!game->textures[i].width || game->textures[i].height
			% game->textures[i].width)
			*err = 1;
	if (!(*err))
	{
		ft_getsprites(game);
		i = game->numsprites;
		while (i--)
		{
			if (!game->textures[4 + game->sprites[i].type].addr)
			{
				game->textures[4
					+ game->sprites[i].type].img = mlx_xpm_file_to_image(game->mlx.mlx,
						"textures/pillar.xpm",
						&game->textures[4 + game->sprites[i].type].width,
						&game->textures[4 + game->sprites[i].type].height);
				if (!game->textures[4 + game->sprites[i].type].img)
					return ;
				game->textures[4
					+ game->sprites[i].type].addr = mlx_get_data_addr(game->textures[4
						+ game->sprites[i].type].img, &game->textures[4
						+ game->sprites[i].type].bpp, &game->textures[4
						+ game->sprites[i].type].ll, &game->textures[4
						+ game->sprites[i].type].endian);
			}
			game->sprites[i].t = &game->textures[4
				+ game->sprites[i].type];
		}
		mlx_loop(game->mlx.mlx);
	}
	else
		ft_dprintf(2, ERR_FORMAT, NAME, TEXTURE_SIZE);
}

int	main(int ac, char **av)
{
	static t_game	game = {0};
	const char		*s;
	int				err;
	int				i;

	if (ac != 2)
		return (ft_dprintf(STDERR_FILENO, ERR_FORMAT, NAME, ARGS_ERR), 1);
	s = ft_strrchr(av[1], '.');
	if (!s)
		return (ft_dprintf(STDERR_FILENO, ERR_FORMAT, NAME, EXT_ERR), 2);
	if (ft_strcmp(s, EXT))
		return (ft_dprintf(STDERR_FILENO, ERR_FORMAT, NAME, EXT_ERR), 2);
	init_map(av[1], &game);
	if (ft_init_mlx(&game))
		return (gc(NULL, 0), 3);
	err = 0;
	if (game.numsprites)
	{
		game.sprites = gc(malloc(game.numsprites * sizeof(t_sprite)), 1);
		game.sprite_dist = gc(malloc(game.numsprites * sizeof(double)), 1);
		game.sprite_order = gc(malloc(game.numsprites * sizeof(int)), 1);
		if (!game.sprites)
			err = 1;
	}
	ft_start(&game, &err);
	mlx_destroy_image(game.mlx.mlx, game.screen.img);
	i = 0;
	while (i < TEXTURES)
		mlx_destroy_image(game.mlx.mlx, game.textures[i++].img);
	return (mlx_destroy_window(game.mlx.mlx, game.mlx.win),
		mlx_destroy_display(game.mlx.mlx), free(game.mlx.mlx), gc(0, 0), 0);
}
