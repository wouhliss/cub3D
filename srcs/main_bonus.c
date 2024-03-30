/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:45:59 by ybelatar          #+#    #+#             */
/*   Updated: 2024/03/30 08:33:57 by wouhliss         ###   ########.fr       */
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
		if (!ft_outside(game, (int)(game->p.pos.x + game->p.dir.x * (speed
						+ (speed * game->shift * 0.6))), (int)game->p.pos.y)
			&& (game->map.map[(int)game->p.pos.y][(int)(game->p.pos.x
					+ game->p.dir.x * (speed + (speed * game->shift
							* 0.6)))] == '0' || game->noclip))
			game->p.pos.x += game->p.dir.x * (speed + (speed * game->shift
						* 0.6));
		if (!ft_outside(game, (int)game->p.pos.x, (int)(game->p.pos.y
					+ game->p.dir.y * (speed + (speed * game->shift * 0.6))))
			&& (game->map.map[(int)(game->p.pos.y + game->p.dir.y * (speed
						+ (speed * game->shift
							* 0.6)))][(int)game->p.pos.x] == '0'
				|| game->noclip))
			game->p.pos.y += game->p.dir.y * (speed + (speed * game->shift
						* 0.6));
	}
	if (game->back)
	{
		if (!ft_outside(game, (int)(game->p.pos.x - game->p.dir.x * (speed
						+ (speed * game->shift * 0.6))), (int)game->p.pos.y)
			&& (game->map.map[(int)game->p.pos.y][(int)(game->p.pos.x
					- game->p.dir.x * (speed + (speed * game->shift
							* 0.6)))] == '0' || game->noclip))
			game->p.pos.x -= game->p.dir.x * (speed + (speed * game->shift
						* 0.6));
		if (!ft_outside(game, (int)game->p.pos.x, (int)(game->p.pos.y
					- game->p.dir.y * (speed + (speed * game->shift * 0.6))))
			&& (game->map.map[(int)(game->p.pos.y - game->p.dir.y * (speed
						+ (speed * game->shift
							* 0.6)))][(int)game->p.pos.x] == '0'
				|| game->noclip))
			game->p.pos.y -= game->p.dir.y * (speed + (speed * game->shift
						* 0.6));
	}
	if (game->right)
	{
		if (!ft_outside(game, (int)(game->p.pos.x + (game->p.dir.x
						* cos(-HALF_PI) - game->p.dir.y * sin(-HALF_PI))
					* (speed + (speed * game->shift * 0.6))),
				(int)game->p.pos.y)
			&& (game->map.map[(int)game->p.pos.y][(int)(game->p.pos.x
					+ (game->p.dir.x * cos(-HALF_PI) - game->p.dir.y
						* sin(-HALF_PI)) * (speed + (speed * game->shift
							* 0.6)))] == '0' || game->noclip))
			game->p.pos.x += (game->p.dir.x * cos(-HALF_PI) - game->p.dir.y
					* sin(-HALF_PI)) * (speed + (speed * game->shift * 0.6));
		if (!ft_outside(game, (int)game->p.pos.x, (int)(game->p.pos.y
					+ (game->p.dir.x * sin(-HALF_PI) + game->p.dir.y
						* cos(-HALF_PI)) * (speed + (speed * game->shift
							* 0.6)))) && (game->map.map[(int)(game->p.pos.y
					+ (game->p.dir.x * sin(-HALF_PI) + game->p.dir.y
						* cos(-HALF_PI)) * (speed + (speed * game->shift
							* 0.6)))][(int)game->p.pos.x] == '0'
				|| game->noclip))
			game->p.pos.y += (game->p.dir.x * sin(-HALF_PI) + game->p.dir.y
					* cos(-HALF_PI)) * (speed + (speed * game->shift * 0.6));
	}
	if (game->left)
	{
		if (!ft_outside(game, (int)(game->p.pos.x + (game->p.dir.x
						* cos(HALF_PI) - game->p.dir.y * sin(HALF_PI)) * (speed
						+ (speed * game->shift * 0.6))), (int)game->p.pos.y)
			&& (game->map.map[(int)game->p.pos.y][(int)(game->p.pos.x
					+ (game->p.dir.x * cos(HALF_PI) - game->p.dir.y
						* sin(HALF_PI)) * (speed + (speed * game->shift
							* 0.6)))] == '0' || game->noclip))
			game->p.pos.x += (game->p.dir.x * cos(HALF_PI) - game->p.dir.y
					* sin(HALF_PI)) * (speed + (speed * game->shift * 0.6));
		if (!ft_outside(game, (int)game->p.pos.x, (int)(game->p.pos.y
					+ (game->p.dir.x * sin(HALF_PI) + game->p.dir.y
						* cos(HALF_PI)) * (speed + (speed * game->shift
							* 0.6)))) && (game->map.map[(int)(game->p.pos.y
					+ (game->p.dir.x * sin(HALF_PI) + game->p.dir.y
						* cos(HALF_PI)) * (speed + (speed * game->shift
							* 0.6)))][(int)game->p.pos.x] == '0'
				|| game->noclip))
			game->p.pos.y += (game->p.dir.x * sin(HALF_PI) + game->p.dir.y
					* cos(HALF_PI)) * (speed + (speed * game->shift * 0.6));
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
	t_projectile	*p;
	clock_t			delta;
	int				i;
	double			step;
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
	p = game->projectiles;
	while (p)
	{
		if (p->sprite->hide)
		{
			p = p->next;
			continue ;
		}
		step = 0;
		while (!p->sprite->hide && step < delta * 0.00000002)
		{
			if (p->type == 0 && !ft_outside(game, (int)(p->sprite->pos.x
						+ p->sprite->dir.x * step), (int)(p->sprite->pos.y
						+ p->sprite->dir.y * step))
				&& game->map.map[(int)(p->sprite->pos.y + p->sprite->dir.y
					* step)][(int)(p->sprite->pos.x + p->sprite->dir.x
					* step)] == '1')
			{
				game->map.map[(int)(p->sprite->pos.y + p->sprite->dir.y
						* step)][(int)(p->sprite->pos.x + p->sprite->dir.x
						* step)] = '0';
				p->sprite->hide = 1;
			}
			else if (p->type == 1 && !ft_outside(game, (int)(p->sprite->pos.x
						+ p->sprite->dir.x * step), (int)(p->sprite->pos.y
						+ p->sprite->dir.y * step))
				&& game->map.map[(int)(p->sprite->pos.y + p->sprite->dir.y
					* step)][(int)(p->sprite->pos.x + p->sprite->dir.x
					* step)] == '1')
			{
				game->portal_l.pos = (t_intvec){(int)(p->sprite->pos.x
						+ p->sprite->dir.x * step), (int)(p->sprite->pos.y
						+ p->sprite->dir.y * step)};
				if (p->sprite->pos.x
						+ p->sprite->dir.x * step - (int)(p->sprite->pos.x
						+ p->sprite->dir.x * step) < 0.1 && p->sprite->pos.x
						+ p->sprite->dir.x * step - (int)(p->sprite->pos.x
						+ p->sprite->dir.x * step) < p->sprite->pos.y
						+ p->sprite->dir.y * step - (int)(p->sprite->pos.y
						+ p->sprite->dir.y * step))
						game->portal_l.side = -1;
				else if (p->sprite->pos.x
						+ p->sprite->dir.x * step - (int)(p->sprite->pos.x
						+ p->sprite->dir.x * step) > 0.9 && p->sprite->pos.y
						+ p->sprite->dir.y * step - (int)(p->sprite->pos.y
						+ p->sprite->dir.y * step) < p->sprite->pos.x
						+ p->sprite->dir.x * step - (int)(p->sprite->pos.x
						+ p->sprite->dir.x * step))
						game->portal_l.side = -2;
				else if (p->sprite->pos.y
						+ p->sprite->dir.y * step - (int)(p->sprite->pos.y
						+ p->sprite->dir.y * step) < 0.1 && p->sprite->pos.y
						+ p->sprite->dir.y * step - (int)(p->sprite->pos.y
						+ p->sprite->dir.y * step) < p->sprite->pos.x
						+ p->sprite->dir.x * step - (int)(p->sprite->pos.x
						+ p->sprite->dir.x * step))
						game->portal_l.side = 1;
				else if (p->sprite->pos.y
						+ p->sprite->dir.y * step - (int)(p->sprite->pos.y
						+ p->sprite->dir.y * step) > 0.9 && p->sprite->pos.x
						+ p->sprite->dir.x * step - (int)(p->sprite->pos.x
						+ p->sprite->dir.x * step) < p->sprite->pos.y
						+ p->sprite->dir.y * step - (int)(p->sprite->pos.y
						+ p->sprite->dir.y * step))
						game->portal_l.side = 2;
				if (game->portal_l.pos.x == game->portal_r.pos.x && game->portal_l.pos.y == game->portal_r.pos.y && game->portal_l.side == game->portal_r.side)
					game->portal_r.side = 0;
				p->sprite->hide = 1;
			}
			else if (p->type == 2 && !ft_outside(game, (int)(p->sprite->pos.x
						+ p->sprite->dir.x * step), (int)(p->sprite->pos.y
						+ p->sprite->dir.y * step))
				&& game->map.map[(int)(p->sprite->pos.y + p->sprite->dir.y
					* step)][(int)(p->sprite->pos.x + p->sprite->dir.x
					* step)] == '1')
			{
				game->portal_r.pos = (t_intvec){(int)(p->sprite->pos.x
						+ p->sprite->dir.x * step), (int)(p->sprite->pos.y
						+ p->sprite->dir.y * step)};
				if (p->sprite->pos.x
						+ p->sprite->dir.x * step - (int)(p->sprite->pos.x
						+ p->sprite->dir.x * step) < 0.1 && p->sprite->pos.x
						+ p->sprite->dir.x * step - (int)(p->sprite->pos.x
						+ p->sprite->dir.x * step) < p->sprite->pos.y
						+ p->sprite->dir.y * step - (int)(p->sprite->pos.y
						+ p->sprite->dir.y * step))
						game->portal_r.side = -1;
				else if (p->sprite->pos.x
						+ p->sprite->dir.x * step - (int)(p->sprite->pos.x
						+ p->sprite->dir.x * step) > 0.9 && p->sprite->pos.y
						+ p->sprite->dir.y * step - (int)(p->sprite->pos.y
						+ p->sprite->dir.y * step) < p->sprite->pos.x
						+ p->sprite->dir.x * step - (int)(p->sprite->pos.x
						+ p->sprite->dir.x * step))
						game->portal_r.side = -2;
				else if (p->sprite->pos.y
						+ p->sprite->dir.y * step - (int)(p->sprite->pos.y
						+ p->sprite->dir.y * step) < 0.1 && p->sprite->pos.y
						+ p->sprite->dir.y * step - (int)(p->sprite->pos.y
						+ p->sprite->dir.y * step) < p->sprite->pos.x
						+ p->sprite->dir.x * step - (int)(p->sprite->pos.x
						+ p->sprite->dir.x * step))
						game->portal_r.side = 1;
				else if (p->sprite->pos.y
						+ p->sprite->dir.y * step - (int)(p->sprite->pos.y
						+ p->sprite->dir.y * step) > 0.9 && p->sprite->pos.x
						+ p->sprite->dir.x * step - (int)(p->sprite->pos.x
						+ p->sprite->dir.x * step) < p->sprite->pos.y
						+ p->sprite->dir.y * step - (int)(p->sprite->pos.y
						+ p->sprite->dir.y * step))
						game->portal_r.side = 2;
				if (game->portal_l.pos.x == game->portal_r.pos.x && game->portal_l.pos.y == game->portal_r.pos.y && game->portal_l.side == game->portal_r.side)
					game->portal_l.side = 0;
				p->sprite->hide = 1;
			}
			step += 0.01;
		}
		p->sprite->pos = (t_vec){p->sprite->pos.x + p->sprite->dir.x * delta
			* 0.00000002, p->sprite->pos.y + p->sprite->dir.y * delta
			* 0.00000002};
		p = p->next;
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
			usleep(100);
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

inline int	ft_loadsprites(t_game *game)
{
	char		*strs[5] = {"textures/pillar.xpm", "textures/barril.xpm",
				"textures/barril.xpm", "textures/pillar.xpm",
				"textures/barril.xpm"};
	t_sprite	*sprite;

	sprite = game->sprites;
	while (sprite)
	{
		if (!game->textures[4 + sprite->type].addr)
		{
			game->textures[4
				+ sprite->type].img = mlx_xpm_file_to_image(game->mlx.mlx,
					strs[sprite->type], &game->textures[4 + sprite->type].width,
					&game->textures[4 + sprite->type].height);
			if (!game->textures[4 + sprite->type].img)
				return (1);
			game->textures[4
				+ sprite->type].addr = mlx_get_data_addr(game->textures[4
					+ sprite->type].img, &game->textures[4 + sprite->type].bpp,
					&game->textures[4 + sprite->type].ll, &game->textures[4
					+ sprite->type].endian);
			if (!game->textures[4 + sprite->type].width || game->textures[4
				+ sprite->type].height % game->textures[4 + sprite->type].width)
				return (1);
			game->textures[4 + sprite->type].frames = game->textures[4
				+ sprite->type].height / game->textures[4 + sprite->type].width;
		}
		sprite->t = &game->textures[4 + sprite->type];
		sprite = sprite->next;
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
	ft_start(&game, &err);
	mlx_destroy_image(game.mlx.mlx, game.screen.img);
	i = -1;
	while (++i < 8)
		if (game.textures[i].img)
			mlx_destroy_image(game.mlx.mlx, game.textures[i].img);
	ft_spritesclear(&game);
	ft_projectilesclear(&game);
	return (mlx_destroy_window(game.mlx.mlx, game.mlx.win),
		mlx_destroy_display(game.mlx.mlx), free(game.mlx.mlx), gc(0, 0), 0);
}
