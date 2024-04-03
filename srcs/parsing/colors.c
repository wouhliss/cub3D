/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:08:38 by ybelatar          #+#    #+#             */
/*   Updated: 2024/04/03 17:02:31 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static int	only_num(const char *color)
{
	while (*color)
	{
		if (*color < '0' || *color > '9')
			return (0);
		++color;
	}
	return (1);
}

static int	in_range(const char *color)
{
	int	c;

	c = ft_atoc(color);
	return (c >= 0 && c <= 255);
}

int	check_args_colors(char **colors)
{
	if (!only_num(colors[0]) || !only_num(colors[1]) || !only_num(colors[2]))
		return (0);
	if (!in_range(colors[0]) || !in_range(colors[1]) || !in_range(colors[2]))
		return (0);
	return (1);
}

int	get_color(char *line, int a, t_game *game)
{
	char	**splitted;

	splitted = gc(ft_split(line, ','), ADD);
	if (!splitted || plen(splitted) != 3)
		return (0);
	if (!check_args_colors(splitted))
		return (0);
	if (a)
	{
		game->colors_c[T] = 1;
		game->colors_c[R] = ft_atoc(splitted[0]);
		game->colors_c[G] = ft_atoc(splitted[1]);
		game->colors_c[B] = ft_atoc(splitted[2]);
	}
	else
	{
		game->colors_f[T] = 1;
		game->colors_f[R] = ft_atoc(splitted[0]);
		game->colors_f[G] = ft_atoc(splitted[1]);
		game->colors_f[B] = ft_atoc(splitted[2]);
	}
	return (1);
}

int	set_colors(char *line, t_game *game)
{
	char	**splitted;

	splitted = gc(ft_split(line, ' '), ADD);
	if (!splitted || plen(splitted) != 2)
		return (0);
	if (!ft_strcmp(splitted[0], "C") && game->colors_c[0])
		return (0);
	if (!ft_strcmp(splitted[0], "F") && game->colors_f[0])
		return (0);
	if (!ft_strcmp(splitted[0], "C"))
		return (get_color(splitted[1], 1, game));
	if (!ft_strcmp(splitted[0], "F"))
		return (get_color(splitted[1], 0, game));
	return (1);
}
