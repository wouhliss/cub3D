/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:45:59 by ybelatar          #+#    #+#             */
/*   Updated: 2024/04/24 23:46:25 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_close_fd(bool to_close, int new_fd)
{
	static int	fd = -1;

	if (to_close && fd > 2)
	{
		close(fd);
		fd = -1;
	}
	else
		fd = new_fd;
}

void	__attribute__((destructor))	aftermain(void)
{
	gc(NULL, EMPTY);
	ft_close_fd(true, 0);
}

static inline void	ft_default_texture(t_game *g)
{
	g->dfl.a = g->dfl_a;
	g->dfl.bpp = 8;
	g->dfl.endian = 2;
	g->dfl.f = 0;
	g->dfl.frames = 0;
	g->dfl.height = 2;
	g->dfl.w = 2;
	g->dfl.img = 0;
	g->dfl.ll = 2;
	g->dfl.s = 0;
	*(((unsigned int *)g->dfl.a)) = 0x00A020F0;
	*(((unsigned int *)g->dfl.a) + 1) = 0;
	*(((unsigned int *)g->dfl.a) + 2) = 0;
	*(((unsigned int *)g->dfl.a) + 3) = 0x00A020F0;
}

void	destroy(t_game *game)
{
	int	i;

	mlx_destroy_image(game->mlx.mlx, game->s.img);
	i = -1;
	while (++i < WTEXTURES)
		if (game->wt[i].img)
			mlx_destroy_image(game->mlx.mlx, game->wt[i].img);
	i = -1;
	while (++i < STEXTURES)
		if (game->st[i].img)
			mlx_destroy_image(game->mlx.mlx, game->st[i].img);
	i = -1;
	while (++i < GLASS)
		if (game->gt[i].img)
			mlx_destroy_image(game->mlx.mlx, game->gt[i].img);
	i = -1;
	while (++i < PTEXTURES)
		if (game->pt[i].img)
			mlx_destroy_image(game->mlx.mlx, game->pt[i].img);
	mlx_destroy_window(game->mlx.mlx, game->mlx.win);
	mlx_destroy_display(game->mlx.mlx);
	free(game->mlx.mlx);
}

int	main(int ac, char **av)
{
	static t_game	game = {0};
	const char		*s;

	if (ac != 2)
		return (ft_dprintf(STDERR_FILENO, ERR_FORMAT, NAME, ARGS_ERR), 1);
	s = ft_strrchr(av[1], '.');
	if (!s || ft_strcmp(s, EXT))
		return (ft_dprintf(STDERR_FILENO, ERR_FORMAT, NAME, EXT_ERR), 2);
	game.fd = -1;
	init_map(av[1], &game);
	ft_default_texture(&game);
	if (ft_init_mlx(&game))
		return (3);
	game.texturec = WTEXTURES;
	game.s.lratio = 0.25;
	game.s.rratio = 0.75;
	ft_start(&game);
	destroy(&game);
	return (0);
}
