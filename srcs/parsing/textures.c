/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 07:49:28 by wouhliss          #+#    #+#             */
/*   Updated: 2024/03/13 02:52:09 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	set_texture(char *line, t_game *game)
{
	char	**splitted;

	splitted = gc(ft_split(line, ' '), 1);
	if (!splitted || plen(splitted) != 2)
		return (0);
	if (!ft_strcmp(splitted[0], "NO") && game->files[0])
		return (0);
	if (!ft_strcmp(splitted[0], "SO") && game->files[1])
		return (0);
	if (!ft_strcmp(splitted[0], "WE") && game->files[2])
		return (0);
	if (!ft_strcmp(splitted[0], "EA") && game->files[3])
		return (0);
	if (!ft_strcmp(splitted[0], "NO"))
		game->files[0] = gc(ft_strdup(splitted[1]), 1);
	if (!ft_strcmp(splitted[0], "SO"))
		game->files[1] = gc(ft_strdup(splitted[1]), 1);
	if (!ft_strcmp(splitted[0], "WE"))
		game->files[2] = gc(ft_strdup(splitted[1]), 1);
	if (!ft_strcmp(splitted[0], "EA"))
		game->files[3] = gc(ft_strdup(splitted[1]), 1);
	return (1);
}
