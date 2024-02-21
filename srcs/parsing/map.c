/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:06:38 by ybelatar          #+#    #+#             */
/*   Updated: 2024/02/21 15:56:54 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	get_map(t_game *game, char *line)
{
	while (line)
	{
		if (!*line)
		{
			//get_next_line(-42);
			panic(MAP_ERR);
		}
		game->map.map = gc(join_tab(game->map.map, line), 1);
		game->length++;
		game->width = max(game->width, ft_strlen(line));
		//line = gc(get_next_line(game->fd), 1);
	}
	if (!game->map.map)
		panic(MAP_ERR);
}

int	set_texture_color(char *line, int *c, t_game *game)
{
	int	i;

	i = 0;
	if (!ft_strncmp(line, "NO ", 3))
		return ((*c)++, set_texture(line, game));
	else if (!ft_strncmp(line, "SO ", 3))
		return ((*c)++, set_texture(line, game));
	else if (!ft_strncmp(line, "WE ", 3))
		return ((*c)++, set_texture(line, game));
	else if (!ft_strncmp(line, "EA ", 3))
		return ((*c)++, set_texture(line, game));
	else if (!ft_strncmp(line, "F ", 2))
		return ((*c)++, set_colors(line, game));
	else if (!ft_strncmp(line, "C ", 2))
		return ((*c)++, set_colors(line, game));
	else if (!*line)
		return (1);
	return (0);
}

void	get_info_map(t_game *game)
{
	int		c;
	char	*line = NULL;

	//line = gc(get_next_line(game->fd), 1);
	// if (!line)
	// 	panic(MAP_ERR);
	c = 0;
	while (line && *line != '1' && *line != ' ')
	{
		if (!set_texture_color(line, &c, game))
		{
			//get_next_line(-42);
			panic(MAP_ERR);
		}
		// line = gc(get_next_line(game->fd), 1);
		// if (!line)
		// 	panic(MAP_ERR);
	}
	if (c != 6)
	{
		//get_next_line(-42);
		panic(MAP_ERR);
	}
	get_map(game, line);
}
