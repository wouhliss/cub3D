/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 07:13:46 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/24 19:55:43 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_outside(const t_game *game, const int x, const int y)
{
	return (x < 0 || x >= game->w || y < 0 || y >= game->length);
}

void	my_mlx_pixel_tput(const t_screen *data, const int x, const int y,
		unsigned int color)
{
	char	*dst;
	t_color	tcolor;
	t_color	scolor;
	t_color	dcolor;

	dst = data->a + (y * data->ll + x * (data->bpp / 8));
	scolor.hex = *(unsigned int *)dst;
	tcolor.hex = color;
	dcolor.t = (data->lratio * scolor.t) + (data->rratio * tcolor.t);
	dcolor.red = (data->lratio * scolor.red) + (data->rratio * tcolor.red);
	dcolor.green = (data->lratio * scolor.green) + (data->rratio
			* tcolor.green);
	dcolor.blue = (data->lratio * scolor.blue) + (data->rratio * tcolor.blue);
	*(unsigned int *)dst = dcolor.hex;
}

bool	ft_can_step(t_game *g, t_sprite *s)
{
	size_t	i;

	if (g->m.m[(int)s->pos.y][(int)s->pos.x] == '1')
		return (false);
	else if (g->m.m[(int)s->pos.y][(int)s->pos.x] == '0')
		return (true);
	else if (g->m.m[(int)s->pos.y][(int)s->pos.x] == 't')
		return (true);
	i = 0;
	while (i < g->doors.index)
	{
		if (g->doors.u_ptr.d[i].pos.x == (int)s->pos.x
			&& g->doors.u_ptr.d[i].pos.y == (int)s->pos.y)
			return (g->doors.u_ptr.d[i].state == OPEN);
		++i;
	}
	return (true);
}

t_intvec	ft_get_facing_int(const int side, t_intvec vec)
{
	if (side == -2)
		++vec.x;
	else if (side == -1)
		--vec.x;
	else if (side == 2)
		++vec.y;
	else if (side == 1)
		--vec.y;
	return (vec);
}

t_vec	ft_get_facing(const int side, t_vec vec)
{
	if (side == -2)
		++vec.x;
	else if (side == -1)
		--vec.x;
	else if (side == 2)
		++vec.y;
	else if (side == 1)
		--vec.y;
	return (vec);
}
