/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:09:11 by ybelatar          #+#    #+#             */
/*   Updated: 2024/01/31 04:54:06 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	set_texture(char *line, t_game *game)
{
	char	**splitted;

	splitted = gc(ft_split(line, ' '), 1);
	if (!splitted || plen(splitted) != 2)
		return (0);
	if (!ft_strcmp(splitted[0], "NO") && game->textures[0])
		return (0);
	if (!ft_strcmp(splitted[0], "SO") && game->textures[1])
		return (0);
	if (!ft_strcmp(splitted[0], "WE") && game->textures[2])
		return (0);
	if (!ft_strcmp(splitted[0], "EA") && game->textures[3])
		return (0);
	if (!ft_strcmp(splitted[0], "NO"))
		game->textures[0] = gc(ft_strdup(splitted[1]), 1);
	if (!ft_strcmp(splitted[0], "SO"))
		game->textures[1] = gc(ft_strdup(splitted[1]), 1);
	if (!ft_strcmp(splitted[0], "WE"))
		game->textures[2] = gc(ft_strdup(splitted[1]), 1);
	if (!ft_strcmp(splitted[0], "EA"))
		game->textures[3] = gc(ft_strdup(splitted[1]), 1);
	return (1);
}
