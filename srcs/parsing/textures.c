/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 07:49:28 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/24 21:13:24 by ybelatar         ###   ########.fr       */
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

static inline void	ft_save_wfiles(t_game *game, char **splitted,
		char **splitted_pf)
{
	if (!ft_strcmp(splitted[0], "NO"))
	{
		game->files[TNO] = gc(ft_strdup(splitted_pf[0]), ADD);
		if (plen(splitted_pf) == 2)
			game->wframes[TNO] = ft_atoi(splitted_pf[1]);
	}
	if (!ft_strcmp(splitted[0], "SO"))
	{
		game->files[TSO] = gc(ft_strdup(splitted_pf[0]), ADD);
		if (plen(splitted_pf) == 2)
			game->wframes[TSO] = ft_atoi(splitted_pf[1]);
	}
	if (!ft_strcmp(splitted[0], "WE"))
	{
		game->files[TWE] = gc(ft_strdup(splitted_pf[0]), ADD);
		if (plen(splitted_pf) == 2)
			game->wframes[TWE] = ft_atoi(splitted_pf[1]);
	}
	if (!ft_strcmp(splitted[0], "EA"))
	{
		game->files[TEA] = gc(ft_strdup(splitted_pf[0]), ADD);
		if (plen(splitted_pf) == 2)
			game->wframes[TEA] = ft_atoi(splitted_pf[1]);
	}
}

static inline void	ft_save_sfiles(t_game *game, char **splitted,
		char **splitted_pf)
{
	if (!ft_strcmp(splitted[0], "D"))
	{
		game->files[TD] = gc(ft_strdup(splitted_pf[0]), ADD);
		if (plen(splitted_pf) == 2)
			game->wframes[TD] = ft_atoi(splitted_pf[1]);
	}
	if (!ft_strcmp(splitted[0], "P"))
	{
		game->sfiles[TP] = gc(ft_strdup(splitted_pf[0]), ADD);
		if (plen(splitted_pf) == 2)
			game->sframes[TP] = ft_atoi(splitted_pf[1]);
	}
	if (!ft_strcmp(splitted[0], "B"))
	{
		game->sfiles[TB] = gc(ft_strdup(splitted_pf[0]), ADD);
		if (plen(splitted_pf) == 2)
			game->sframes[TB] = ft_atoi(splitted_pf[1]);
	}
}

int	set_texture(char *line, t_game *game)
{
	char	**sp;
	char	**sp_pf;

	sp = gc(ft_split(line, ' '), ADD);
	if (!sp || plen(sp) != 2)
		return (0);
	sp_pf = gc(ft_split(sp[1], ':'), ADD);
	if (!sp_pf || plen(sp_pf) > 2)
		return (0);
	if (plen(sp_pf) == 2 && (!only_num(sp_pf[1])
			|| ft_atoi(sp_pf[1]) == (long)INT_MAX + 1))
		return (0);
	if ((!ft_strcmp(sp[0], "NO") && game->files[TNO]) || (!ft_strcmp(sp[0],
				"SO") && game->files[TSO]) || (!ft_strcmp(sp[0], "WE")
			&& game->files[TWE]) || (!ft_strcmp(sp[0], "EA")
			&& game->files[TEA]) || (!ft_strcmp(sp[0], "D") && game->files[TD])
		|| (!ft_strcmp(sp[0], "P") && game->sfiles[TP]) || (!ft_strcmp(sp[0],
				"B") && game->sfiles[TB]))
		return (0);
	ft_save_wfiles(game, sp, sp_pf);
	ft_save_sfiles(game, sp, sp_pf);
	return (1);
}
