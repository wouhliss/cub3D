/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 21:14:59 by ybelatar          #+#    #+#             */
/*   Updated: 2024/04/24 21:20:56 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_import_portals(t_game *g, const char **pt)
{
	int	i;

	i = -1;
	while (pt[++i])
	{
		g->pt[i].img = mlx_xpm_file_to_image(g->mlx.mlx,
				(char *)gc(ft_mprintf("%s%s", "assets/textures/walls/", pt[i]),
					ADD), &g->pt[i].w, &g->pt[i].height);
		if (!g->pt[i].img)
		{
			g->pt[i] = g->dfl;
			g->pt[i].img = 0;
		}
		else
			g->pt[i].a = mlx_get_data_addr(g->pt[i].img, &g->pt[i].bpp,
					&g->pt[i].ll, &g->pt[i].endian);
	}
}

void	ft_import_glass(t_game *g, const char **gt)
{
	int	i;

	i = -1;
	while (gt[++i])
	{
		g->gt[i].img = mlx_xpm_file_to_image(g->mlx.mlx,
				(char *)gc(ft_mprintf("%s%s", "assets/textures/walls/", gt[i]),
					ADD), &g->gt[i].w, &g->gt[i].height);
		if (!g->gt[i].img)
		{
			g->gt[i] = g->dfl;
			g->gt[i].img = 0;
		}
		else
			g->gt[i].a = mlx_get_data_addr(g->gt[i].img, &g->gt[i].bpp,
					&g->gt[i].ll, &g->gt[i].endian);
	}
}

void	ft_import_sprites(t_game *g)
{
	int	i;

	i = -1;
	while (++i < STEXTURES)
	{
		if (g->sfiles[i])
			g->st[i].img = mlx_xpm_file_to_image(g->mlx.mlx, g->sfiles[i],
					&g->st[i].w, &g->st[i].height);
		if (!g->st[i].img)
		{
			g->st[i] = g->dfl;
			g->st[i].img = 0;
		}
		else
			g->st[i].a = mlx_get_data_addr(g->st[i].img, &g->st[i].bpp,
					&g->st[i].ll, &g->st[i].endian);
	}
}

bool	ft_check_walls(t_game *g)
{
	int	i;

	i = WTEXTURES;
	while (i--)
	{
		if (!g->wt[i].w || g->wt[i].height % g->wt[i].w)
			return (true);
		else
			g->wt[i].frames = g->wt[i].height / g->wt[i].w;
	}
	return (false);
}

bool	ft_check_sprites(t_game *g)
{
	int	i;

	i = STEXTURES;
	while (i--)
	{
		if (!g->st[i].a)
			continue ;
		if (!g->st[i].w || g->st[i].height % g->st[i].w)
			return (true);
		g->st[i].frames = g->st[i].height / g->st[i].w;
	}
	return (false);
}
