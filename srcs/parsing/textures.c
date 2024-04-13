/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 07:49:28 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/12 13:58:39 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

/*
	TODO add parsinfg for texture animation "/assets/text/text.xpm:100" and 100 is the number of ms per frame
*/

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

int	set_texture(char *line, t_game *game)
{
	char	**splitted;
	char	**splitted_pf;

	splitted = gc(ft_split(line, ' '), ADD);
	if (!splitted || plen(splitted) != 2)
		return (0);
	splitted_pf = gc(ft_split(splitted[1], ':'), ADD);
    if (!splitted_pf || plen(splitted_pf) > 2)
		return (0);
	if (plen(splitted_pf) == 2 && (!only_num(splitted_pf[1]) || ft_atoi(splitted_pf[1]) == (long)INT_MAX + 1))
		return (0);
	if (!ft_strcmp(splitted[0], "NO") && game->files[TNO])
		return (0);
	if (!ft_strcmp(splitted[0], "SO") && game->files[TSO])
		return (0);
	if (!ft_strcmp(splitted[0], "WE") && game->files[TWE])
		return (0);
	if (!ft_strcmp(splitted[0], "EA") && game->files[TEA])
		return (0);
	if (!ft_strcmp(splitted[0], "D") && game->files[TD])
		return (0);
	if (!ft_strcmp(splitted[0], "B") && game->files[TB])
		return (0);
	if (!ft_strcmp(splitted[0], "NO"))
	{
		game->files[TNO] = gc(ft_strdup(splitted_pf[0]), ADD);
		if (plen(splitted_pf) == 2)
			game->timeframes[TNO] = ft_atoi(splitted_pf[1]);
	}
	if (!ft_strcmp(splitted[0], "SO"))
	{
		game->files[TSO] = gc(ft_strdup(splitted_pf[0]), ADD);
		if (plen(splitted_pf) == 2)
			game->timeframes[TSO] = ft_atoi(splitted_pf[1]);
	}
	if (!ft_strcmp(splitted[0], "WE"))
	{
		game->files[TWE] = gc(ft_strdup(splitted_pf[0]), ADD);
		if (plen(splitted_pf) == 2)
			game->timeframes[TWE] = ft_atoi(splitted_pf[1]);
	}
	if (!ft_strcmp(splitted[0], "EA"))
	{
		game->files[TEA] = gc(ft_strdup(splitted_pf[0]), ADD);
		if (plen(splitted_pf) == 2)
			game->timeframes[TEA] = ft_atoi(splitted_pf[1]);
	}
	if (!ft_strcmp(splitted[0], "D"))
	{
		game->files[TD] = gc(ft_strdup(splitted_pf[0]), ADD);
		if (plen(splitted_pf) == 2)
			game->timeframes[TD] = ft_atoi(splitted_pf[1]);
	}
	if (!ft_strcmp(splitted[0], "B"))
	{
		game->files[TB] = gc(ft_strdup(splitted_pf[0]), ADD);
		if (plen(splitted_pf) == 2)
			game->timeframes[TB] = ft_atoi(splitted_pf[1]);
	}
	return (1);
}
