/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:06:38 by ybelatar          #+#    #+#             */
/*   Updated: 2024/04/24 19:18:44 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	get_map(t_game *game, char *line)
{
	while (line)
	{
		game->m.m = gc(join_tab(game->m.m, line), ADD);
		game->length++;
		game->w = max(game->w, ft_strlen(line));
		line = gc(get_next_line(game->fd), ADD);
	}
	if (!game->m.m)
		panic(MAP_ERR);
}

int	set_texture_color(char *line, int *c, t_game *game)
{
	if (!ft_strncmp(line, "NO ", 3))
		return ((*c)++, set_texture(line, game));
	else if (!ft_strncmp(line, "SO ", 3))
		return ((*c)++, set_texture(line, game));
	else if (!ft_strncmp(line, "WE ", 3))
		return ((*c)++, set_texture(line, game));
	else if (!ft_strncmp(line, "EA ", 3))
		return ((*c)++, set_texture(line, game));
	else if (!ft_strncmp(line, "D ", 2))
		return (set_texture(line, game));
	else if (!ft_strncmp(line, "B ", 2))
		return (set_texture(line, game));
	else if (!ft_strncmp(line, "P ", 2))
		return (set_texture(line, game));
	else if (!ft_strncmp(line, "F ", 2))
		return ((*c)++, set_colors(line, game));
	else if (!ft_strncmp(line, "C ", 2))
		return ((*c)++, set_colors(line, game));
	else if (!(*line))
		return (1);
	return (0);
}

void	get_info_map(t_game *game)
{
	int		c;
	char	*line;

	line = gc(get_next_line(game->fd), ADD);
	if (!line)
		panic(EMPTY_ERR);
	c = 0;
	while (line && *line != '1' && *line != ' ')
	{
		if (!set_texture_color(line, &c, game))
		{
			get_next_line(EMPTY_BUFFER);
			panic(INVALID_ERR);
		}
		line = gc(get_next_line(game->fd), ADD);
		if (!line)
			panic(MISSING_ERR);
	}
	if (c != PARAMS)
	{
		get_next_line(EMPTY_BUFFER);
		panic(SETTINGS_ERR);
	}
	get_map(game, line);
}
