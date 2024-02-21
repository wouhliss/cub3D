/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:45:59 by ybelatar          #+#    #+#             */
/*   Updated: 2024/02/21 15:11:04 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static inline int	check_extension(char *path)
{
	const char	*s;

	if (!path)
		return (0);
	s = ft_strchr(path, '.');
	if (!s)
		return (0);
	return (!ft_strcmp(s, EXT));
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
	{
		ft_dprintf(2, ERR_FORMAT, NAME, ERR_ARGS);
		return (1);
	}
	if (!check_extension(av[1]))
	{
		ft_dprintf(2, ERR_FORMAT, NAME, EXT_ERR);
		return (2);
	}
	return (0);
}
