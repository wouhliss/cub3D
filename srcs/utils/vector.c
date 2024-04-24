/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:30:41 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/24 19:19:07 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	*ft_add_to_vector(const t_game *g, t_vector *vec, void *u_ptr)
{
	if (vec->t == DOOR)
	{
		if (vec->index < vec->size || ft_resize_dvector(vec))
			vec->u_ptr.d[vec->index] = *((t_door *)u_ptr);
		return (&vec->u_ptr.d[vec->index++]);
	}
	else if (vec->t == PROJECTILE)
	{
		if (vec->index < vec->size || ft_resize_pvector(vec))
			vec->u_ptr.p[vec->index] = *((t_projectile *)u_ptr);
		return (&vec->u_ptr.p[vec->index++]);
	}
	else if (vec->t == SPRITE)
	{
		if (vec->index < vec->size || ft_resize_svector(g, vec))
			vec->u_ptr.s[vec->index] = *((t_sprite *)u_ptr);
		return (&vec->u_ptr.s[vec->index++]);
	}
	else if (vec->t == HIT)
	{
		if (vec->index < vec->size || ft_resize_hvector(vec))
			vec->u_ptr.h[vec->index] = *((t_hit *)u_ptr);
		return (&vec->u_ptr.h[vec->index++]);
	}
	return (NULL);
}

void	ft_create_vector(t_vector *vector, int t, size_t size)
{
	vector->t = t;
	vector->size = DFL_SIZE;
	vector->bsize = size;
	vector->u_ptr.u_ptr = gc(malloc(vector->size * size), ADD);
	vector->index = 0;
	if (!vector->u_ptr.u_ptr)
		vector->size = 0;
}
