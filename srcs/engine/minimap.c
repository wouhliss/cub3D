/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:04:33 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/25 00:29:35 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static inline void	ft_put_pixel_map(t_game *g, t_intvec *sp, t_intvec *pos,
		t_intvec *draw)
{
	pos->x = sp->x + ((draw->x - MX) >> MS);
	draw->y = MY;
	while (++draw->y < MH + MY && sp->y + ((draw->y - MY) >> MS) < g->length)
	{
		pos->y = sp->y + ((draw->y - MY) >> MS);
		if (g->m.m[pos->y][pos->x] == '1')
			my_mlx_pixel_tput(&g->s, draw->x, draw->y, 0x00000000);
		else if (g->m.m[pos->y][pos->x] == 'D')
			my_mlx_pixel_tput(&g->s, draw->x, draw->y, 0x00333333);
		else if (ic("eryuiopadfghjklzxt", g->m.m[pos->y][pos->x]))
			my_mlx_pixel_tput(&g->s, draw->x, draw->y, 0x00AAAAAA);
		else
			my_mlx_pixel_tput(&g->s, draw->x, draw->y, 0x00FFFFFF);
		if (g->pl.side && g->pl.pos.x == pos->x
			&& g->pl.pos.y == pos->y)
			my_mlx_pixel_tput(&g->s, draw->x, draw->y, 0x0000AAFF);
		else if (g->pr.side && g->pr.pos.x == pos->x
			&& g->pr.pos.y == pos->y)
			my_mlx_pixel_tput(&g->s, draw->x, draw->y, 0x00FFAA00);
		if ((int)g->p.pos.x == pos->x && (int)g->p.pos.y == pos->y)
			my_mlx_pixel_tput(&g->s, draw->x, draw->y, 0x00FF0000);
	}
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
	while (++draw.x < MW + MX && sp.x + ((draw.x - MX) >> MS) < g->w)
	{
		ft_put_pixel_map(g, &sp, &pos, &draw);
	}
}
