/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:45:59 by ybelatar          #+#    #+#             */
/*   Updated: 2024/03/28 15:34:37 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static inline void	ft_handleinput(t_game *game, double delta)
{
	double	x;
	double	speed;
	double	sens;

	speed = (delta * 0.000000005);
	sens = 0.000000008 * delta;
	if (game->front)
	{
		if ((int)(game->p.pos.x + game->p.dir.x * (speed + (speed * game->shift
						* 0.6))) > 0 && (int)(game->p.pos.x + game->p.dir.x
				* (speed + (speed * game->shift * 0.6))) < game->width
			&& (game->map.map[(int)game->p.pos.y][(int)(game->p.pos.x
					+ game->p.dir.x * (speed + (speed * game->shift
							* 0.6)))] == '0' || game->noclip))
			game->p.pos.x += game->p.dir.x * (speed + (speed * game->shift
						* 0.6));
		if ((int)(game->p.pos.y + game->p.dir.y * (speed + (speed * game->shift
						* 0.6))) > 0 && (int)(game->p.pos.y + game->p.dir.y
				* (speed + (speed * game->shift * 0.6))) < game->length
			&& (game->map.map[(int)(game->p.pos.y + game->p.dir.y * (speed
						+ (speed * game->shift
							* 0.6)))][(int)game->p.pos.x] == '0'
				|| game->noclip))
			game->p.pos.y += game->p.dir.y * (speed + (speed * game->shift
						* 0.6));
	}
	if (game->back)
	{
		if ((int)(game->p.pos.x - game->p.dir.x * (speed + (speed * game->shift
						* 0.6))) > 0 && (int)(game->p.pos.x - game->p.dir.x
				* (speed + (speed * game->shift * 0.6))) < game->width
			&& (game->map.map[(int)game->p.pos.y][(int)(game->p.pos.x
					- game->p.dir.x * (speed + (speed * game->shift
							* 0.6)))] == '0' || game->noclip))
			game->p.pos.x -= game->p.dir.x * (speed + (speed * game->shift
						* 0.6));
		if ((int)(game->p.pos.y - game->p.dir.y * (speed + (speed * game->shift
						* 0.6))) > 0 && (int)(game->p.pos.y - game->p.dir.y
				* (speed + (speed * game->shift * 0.6))) < game->length
			&& (game->map.map[(int)(game->p.pos.y - game->p.dir.y * (speed
						+ (speed * game->shift
							* 0.6)))][(int)game->p.pos.x] == '0'
				|| game->noclip))
			game->p.pos.y -= game->p.dir.y * (speed + (speed * game->shift
						* 0.6));
	}
	if (game->right)
	{
		if ((int)(game->p.pos.x + (game->p.dir.x * cos(-HALF_PI) - game->p.dir.y
					* sin(-HALF_PI)) * (speed + (speed * game->shift
						* 0.6))) > 0 && (int)(game->p.pos.x + (game->p.dir.x
					* cos(-HALF_PI) - game->p.dir.y * sin(-HALF_PI)) * (speed
					+ (speed * game->shift * 0.6))) < game->width
			&& (game->map.map[(int)game->p.pos.y][(int)(game->p.pos.x
					+ (game->p.dir.x * cos(-HALF_PI) - game->p.dir.y
						* sin(-HALF_PI)) * (speed + (speed * game->shift
							* 0.6)))] == '0' || game->noclip))
			game->p.pos.x += (game->p.dir.x * cos(-HALF_PI) - game->p.dir.y
					* sin(-HALF_PI)) * (speed + (speed * game->shift * 0.6));
		if ((int)(game->p.pos.y + (game->p.dir.x * sin(-HALF_PI) + game->p.dir.y
					* cos(-HALF_PI)) * (speed + (speed * game->shift
						* 0.6))) > 0 && (int)(game->p.pos.y + (game->p.dir.x
					* sin(-HALF_PI) + game->p.dir.y * cos(-HALF_PI)) * (speed
					+ (speed * game->shift * 0.6))) < game->length
			&& (game->map.map[(int)(game->p.pos.y + (game->p.dir.x
						* sin(-HALF_PI) + game->p.dir.y * cos(-HALF_PI))
					* (speed + (speed * game->shift
							* 0.6)))][(int)game->p.pos.x] == '0'
				|| game->noclip))
			game->p.pos.y += (game->p.dir.x * sin(-HALF_PI) + game->p.dir.y
					* cos(-HALF_PI)) * (speed + (speed * game->shift * 0.6));
	}
	if (game->left)
	{
		if ((int)(game->p.pos.x - (game->p.dir.x * cos(-HALF_PI) - game->p.dir.y
					* sin(-HALF_PI)) * (speed + (speed * game->shift
						* 0.6))) > 0 && (int)(game->p.pos.x - (game->p.dir.x
					* cos(-HALF_PI) - game->p.dir.y * sin(-HALF_PI)) * (speed
					+ (speed * game->shift * 0.6))) < game->width
			&& (game->map.map[(int)game->p.pos.y][(int)(game->p.pos.x
					- (game->p.dir.x * cos(-HALF_PI) - game->p.dir.y
						* sin(-HALF_PI)) * (speed + (speed * game->shift
							* 0.6)))] == '0' || game->noclip))
			game->p.pos.x -= (game->p.dir.x * cos(-HALF_PI) - game->p.dir.y
					* sin(-HALF_PI)) * (speed + (speed * game->shift * 0.6));
		if ((int)(game->p.pos.y - (game->p.dir.x * sin(-HALF_PI) + game->p.dir.y
					* cos(-HALF_PI)) * (speed + (speed * game->shift
						* 0.6))) > 0 && (int)(game->p.pos.y - (game->p.dir.x
					* sin(-HALF_PI) + game->p.dir.y * cos(-HALF_PI)) * (speed
					+ (speed * game->shift * 0.6))) < game->length
			&& (game->map.map[(int)(game->p.pos.y - (game->p.dir.x
						* sin(-HALF_PI) + game->p.dir.y * cos(-HALF_PI))
					* (speed + (speed * game->shift
							* 0.6)))][(int)game->p.pos.x] == '0'
				|| game->noclip))
			game->p.pos.y -= (game->p.dir.x * sin(-HALF_PI) + game->p.dir.y
					* cos(-HALF_PI)) * (speed + (speed * game->shift * 0.6));
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
		game->p.y += (0.000004 * delta);
	if (game->down)
		game->p.y -= (0.000004 * delta);
}

int	ft_loop(void *param)
{
	t_game			*game;
	clock_t			delta;
	int				i;
	struct timespec	t;

	game = param;
	clock_gettime(CLOCK_MONOTONIC_RAW, &t);
	game->now = t.tv_nsec + t.tv_sec * 1000000000;
	if (game->now - game->f > 1000000000)
	{
		printf("%d\n", game->frames);
		game->frames = 0;
		game->f = game->now;
	}
	++game->frames;
	pthread_mutex_lock(&game->state_m);
	game->state = COMPUTING;
	pthread_mutex_unlock(&game->state_m);
	delta = game->now - game->last;
	if (game->now - game->a > 200000000)
	{
		i = -1;
		while (++i < 8)
		{
			if (!game->textures[i].img || game->textures[i].frames == 1)
				continue ;
			++game->textures[i].f;
			if (game->textures[i].f == game->textures[i].frames)
				game->textures[i].f = 0;
			game->textures[i].s = game->textures[i].f * game->textures[i].width
				* game->textures[i].width;
		}
		game->a = game->now;
	}
	ft_handleinput(game, delta);
	game->last = game->now;
	pthread_mutex_lock(&game->state_m);
	game->state = RENDERING;
	pthread_mutex_unlock(&game->state_m);
	i = 0;
	while (i < 4)
	{
		pthread_mutex_lock(&game->rendered_m[i]);
		if (game->rendered[i])
		{
			pthread_mutex_unlock(&game->rendered_m[i]);
			++i;
		}
		else
		{
			pthread_mutex_unlock(&game->rendered_m[i]);
			usleep(500);
		}
	}
	ft_drawmap(game);
	ft_drawsprites(game);
	mlx_put_image_to_window(game->mlx.mlx, game->mlx.win, game->screen.img, 0,
		0);
	pthread_mutex_lock(&game->state_m);
	game->state = DRAWN;
	pthread_mutex_unlock(&game->state_m);
	i = -1;
	while (++i < 4)
	{
		pthread_mutex_lock(&game->rendered_m[i]);
		game->rendered[i] = 0;
		pthread_mutex_unlock(&game->rendered_m[i]);
	}
	return (0);
}

static inline int	ft_import_textures(t_game *g)
{
	int	exit;
	int	i;

	g->screen.addr = mlx_get_data_addr(g->screen.img, &g->screen.bpp,
			&g->screen.ll, &g->screen.endian);
	i = 4;
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

	XInitThreads();
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
	x = -1;
	game->sprites[i] = (t_sprite){.type = 3, .vdiff = 64.0, .hr = 1, .vr = 1,
		.hide = 1};
	game->sprites[i++].pos = game->map.s_pos;
	while (++x < game->width)
	{
		y = -1;
		while (++y < game->length)
		{
			if (game->map.map[y][x] == 'b')
			{
				game->sprites[i] = (t_sprite){.type = 2, .vdiff = 128.0,
					.hr = 2, .vr = 2, .hide = 0};
				game->sprites[i++].pos = (t_vec){x + 0.5, y + 0.5};
				game->map.map[y][x] = '0';
			}
			else if (game->map.map[y][x] == 'B')
			{
				game->sprites[i] = (t_sprite){.type = 1, .vdiff = 64.0, .hr = 1,
					.vr = 1, .hide = 0};
				game->sprites[i++].pos = (t_vec){x + 0.5, y + 0.5};
				game->map.map[y][x] = '0';
			}
			else if (game->map.map[y][x] == 'P')
			{
				game->sprites[i] = (t_sprite){.type = 0, .vdiff = 64.0, .hr = 1,
					.vr = 1, .hide = 0};
				game->sprites[i++].pos = (t_vec){x + 0.5, y + 0.5};
				game->map.map[y][x] = '0';
			}
		}
	}
}

static inline int	ft_loadsprites(t_game *game)
{
	char	*strs[4] = {"textures/pillar.xpm", "textures/barril.xpm",
			"textures/barril.xpm", "textures/pillar.xpm"};
	int		i;

	ft_getsprites(game);
	i = game->numsprites;
	while (i--)
	{
		if (!game->textures[4 + game->sprites[i].type].addr)
		{
			game->textures[4
				+ game->sprites[i].type].img = mlx_xpm_file_to_image(game->mlx.mlx,
					strs[game->sprites[i].type], &game->textures[4
					+ game->sprites[i].type].width, &game->textures[4
					+ game->sprites[i].type].height);
			if (!game->textures[4 + game->sprites[i].type].img)
				return (1);
			game->textures[4
				+ game->sprites[i].type].addr = mlx_get_data_addr(game->textures[4
					+ game->sprites[i].type].img, &game->textures[4
					+ game->sprites[i].type].bpp, &game->textures[4
					+ game->sprites[i].type].ll, &game->textures[4
					+ game->sprites[i].type].endian);
			if (!game->textures[4 + game->sprites[i].type].width
				|| game->textures[4 + game->sprites[i].type].height
				% game->textures[4 + game->sprites[i].type].width)
				return (1);
			game->textures[4 + game->sprites[i].type].frames = game->textures[4
				+ game->sprites[i].type].height / game->textures[4
				+ game->sprites[i].type].width;
		}
		game->sprites[i].t = &game->textures[4 + game->sprites[i].type];
	}
	return (0);
}

static inline void	ft_start(t_game *game, int *err)
{
	int			i;
	t_thread	threads[4];

	i = 4;
	while (i--)
	{
		if (!game->textures[i].width || game->textures[i].height
			% game->textures[i].width)
			*err = 1;
		game->textures[i].frames = game->textures[i].height
			/ game->textures[i].width;
	}
	if (ft_loadsprites(game))
		*err = 2;
	if (!(*err))
	{
		pthread_mutex_init(&game->state_m, NULL);
		i = 0;
		while (i < 4)
		{
			pthread_mutex_init(&game->rendered_m[i], NULL);
			threads[i].id = i;
			threads[i].game = game;
			pthread_create(&threads[i].tid, NULL, ft_thread, &threads[i]);
			++i;
		}
		mlx_loop(game->mlx.mlx);
		pthread_mutex_lock(&game->state_m);
		game->state = ENDED;
		pthread_mutex_unlock(&game->state_m);
		while (i--)
			pthread_join(threads[i].tid, NULL);
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
	if (!s || ft_strcmp(s, EXT))
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
		if (!game.sprites || !game.sprite_dist || !game.sprite_order)
			err = 1;
	}
	ft_start(&game, &err);
	mlx_destroy_image(game.mlx.mlx, game.screen.img);
	i = -1;
	while (++i < 8)
		if (game.textures[i].img)
			mlx_destroy_image(game.mlx.mlx, game.textures[i].img);
	return (mlx_destroy_window(game.mlx.mlx, game.mlx.win),
		mlx_destroy_display(game.mlx.mlx), free(game.mlx.mlx), gc(0, 0), 0);
}
