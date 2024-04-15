/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 05:07:12 by ybelatar          #+#    #+#             */
/*   Updated: 2024/04/15 21:22:16 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	put_colors(t_game *game)
{
	game->map.cc.hex = create_trgb(0, game->colors_c[R], game->colors_c[G],
			game->colors_c[B]);
	game->map.fc.hex = create_trgb(0, game->colors_f[R], game->colors_f[G],
			game->colors_f[B]);
}
