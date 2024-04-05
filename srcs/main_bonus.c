/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:45:59 by ybelatar          #+#    #+#             */
/*   Updated: 2024/04/05 14:58:49 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void __attribute__ ((destructor)) aftermain(void)
{
	gc(NULL, EMPTY);
}

int	main(int ac, char **av)
{
	static t_game	game = {0};
	const char		*s;
	int				i;

	if (ac < 2)
		return (ft_dprintf(STDERR_FILENO, ERR_FORMAT, NAME, ARGS_ERR), 1);
	s = ft_strrchr(av[1], '.');
	if (!s || ft_strcmp(s, EXT))
		return (ft_dprintf(STDERR_FILENO, ERR_FORMAT, NAME, EXT_ERR), 2);
	init_map(av[1], &game);
	if (ft_init_mlx(&game))
		return (3);
	game.texturec = WTEXTURES;
	ft_start(&game);
	mlx_destroy_image(game.mlx.mlx, game.screen.img);
	i = -1;
	while (++i < WTEXTURES)
		mlx_destroy_image(game.mlx.mlx, game.wt[i].img);
	i = -1;
	while (++i < STEXTURES)
		if (game.st[i].img)
			mlx_destroy_image(game.mlx.mlx, game.st[i].img);
	return (mlx_destroy_window(game.mlx.mlx, game.mlx.win),
		mlx_destroy_display(game.mlx.mlx), free(game.mlx.mlx),
		0);
}
