/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 00:57:58 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/24 19:10:07 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static inline void	ft_get_del_linked(const t_game *g,
		t_sprite *s, t_sprite *res)
{
	size_t	i;

	i = 0;
	while (i < g->pls.index)
	{
		if (g->pls.u_ptr.p[i].sprite == s)
		{
			if (s->delete)
				g->pls.u_ptr.p[i].delete = 1;
			else
				g->pls.u_ptr.p[i].sprite = res;
		}
		++i;
	}
}

void	*ft_resize_dvector(t_vector *vector)
{
	t_door	*res;
	size_t	i;
	size_t	j;

	res = gc(ft_calloc(vector->size * 2, vector->bsize), ADD);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (i < vector->index)
	{
		if (!vector->u_ptr.d[i].delete)
			res[j++] = vector->u_ptr.d[i];
		++i;
	}
	vector->u_ptr.d = res;
	vector->size *= 2;
	vector->index = j;
	return (res);
}

void	*ft_resize_pvector(t_vector *vector)
{
	t_projectile	*res;
	size_t			i;
	size_t			j;

	res = gc(ft_calloc(vector->size * 2, vector->bsize), ADD);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (i < vector->index)
	{
		if (!vector->u_ptr.p[i].delete)
			res[j++] = vector->u_ptr.p[i];
		++i;
	}
	vector->u_ptr.p = res;
	vector->size *= 2;
	vector->index = j;
	return (res);
}

void	*ft_resize_svector(const t_game *g, t_vector *vector)
{
	t_sprite		*res;
	size_t			i;
	size_t			j;

	res = gc(ft_calloc(vector->size * 2, vector->bsize), ADD);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (i < vector->index)
	{
		ft_get_del_linked(g, &vector->u_ptr.s[i], &res[j]);
		if (!vector->u_ptr.s[i].delete)
			res[j++] = vector->u_ptr.s[i];
		++i;
	}
	vector->u_ptr.s = res;
	vector->size *= 2;
	vector->index = j;
	return (res);
}

void	*ft_resize_hvector(t_vector *vector)
{
	t_hit	*res;
	size_t	i;
	size_t	j;

	res = gc(ft_calloc(vector->size * 2, vector->bsize), ADD);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (i < vector->index)
		res[j++] = vector->u_ptr.h[i++];
	vector->u_ptr.h = res;
	vector->size *= 2;
	vector->index = j;
	return (res);
}
