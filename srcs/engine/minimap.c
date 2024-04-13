/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:04:33 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/13 11:07:28 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static inline void	my_mlx_pixel_tput(const t_screen *data, const int x, const int y, unsigned int color)
{
	char			*dst;
	t_color			tcolor;
	t_color			scolor;
	t_color			dcolor;

	dst = data->addr + (y * data->ll + x * (data->bpp / 8));
	scolor.hex = *(unsigned int *)dst;
	tcolor.hex = color;
	dcolor.t = (0.35 * scolor.t) + (0.65 * tcolor.t);
	dcolor.red = (0.35 * scolor.red) + (0.65 * tcolor.red);
	dcolor.green = (0.35 * scolor.green) + (0.65 * tcolor.green);
	dcolor.blue = (0.35 * scolor.blue) + (0.65 * tcolor.blue);
	*(unsigned int *)dst = dcolor.hex;
}

void	ft_drawmap(t_game *g)
{
	t_intvec	sp;
	t_intvec	pos;
	t_intvec	draw;

	sp = (t_intvec){g->p.pos.x - MPR, g->p.pos.y - MPR};
	if (sp.x < 0)
		sp.x = 0;
	if (sp.y < 0)
		sp.y = 0;
	draw.x = MX;
	while (++draw.x < MW + MX && sp.x + ((draw.x - MX) >> MS) < g->width)
	{
		pos.x = sp.x + ((draw.x - MX) >> MS);
		draw.y = MY;
		while (++draw.y < MH + MY && sp.y + ((draw.y - MY) >> MS) < g->length)
		{
			pos.y = sp.y + ((draw.y - MY) >> MS);
			if (g->map.map[pos.y][pos.x] == '1')
				my_mlx_pixel_tput(&g->screen, draw.x, draw.y, 0x00000000);
			else
				my_mlx_pixel_tput(&g->screen, draw.x, draw.y, 0x00FFFFFF);
			if ((int)g->p.pos.x == pos.x && (int)g->p.pos.y == pos.y)
				my_mlx_pixel_tput(&g->screen, draw.x, draw.y, 0x00FF0000);
		}
	}
}
