/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:30:41 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/16 01:05:00 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_add_to_vector(t_vector *vec, void *u_ptr)
{
	if (vec->type == DOOR)
	{
		if (vec->index < vec->size || ft_resize_dvector(vec))
			vec->u_ptr.d[vec->index++] = *((t_door *)u_ptr);
	}
	else if (vec->type == PROJECTILE)
	{
		if (vec->index < vec->size || ft_resize_pvector(vec))
			vec->u_ptr.p[vec->index++] = *((t_projectile *)u_ptr);
	}
	else if (vec->type == SPRITE)
	{
		if (vec->index < vec->size || ft_resize_svector(vec))
			vec->u_ptr.s[vec->index++] = *((t_sprite *)u_ptr);
	}
	else if (vec->type == HIT)
	{
		if (vec->index < vec->size || ft_resize_hvector(vec))
			vec->u_ptr.h[vec->index++] = *((t_hit *)u_ptr);
	}
}

void	ft_create_vector(t_vector *vector, int type, size_t size)
{
	vector->type = type;
	vector->size = DFL_SIZE;
	vector->bsize = size;
	vector->u_ptr.u_ptr = gc(malloc(vector->size * size), ADD);
	vector->index = 0;
	if (!vector->u_ptr.u_ptr)
		vector->size = 0;
}
