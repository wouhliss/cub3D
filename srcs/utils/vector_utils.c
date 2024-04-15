/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 11:30:41 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/15 21:31:01 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static inline void	*ft_resize_vector(t_vector *vector)
{
	size_t	*res;
	size_t	i;
	size_t	j;

	res = ft_calloc(vector->size * 2, vector->bsize);
	if (!res)
		return (NULL);
	i = -1;
	j = vector->size * vector->bsize / sizeof(u_int64_t);
	while (++i < j)
		res[i] = vector->u_ptr.ul[i];
	free(vector->u_ptr.u_ptr);
	vector->u_ptr.ul = res;
	vector->size *= 2;
	return (res);
}

void	ft_add_to_vector(t_vector *vec, void *u_ptr)
{
	if (vec->type == DOOR)
	{
		if (vec->index < vec->size || ft_resize_vector(vec))
			vec->u_ptr.d[vec->index++] = *((t_door *)u_ptr);
	}
	else if (vec->type == PROJECTILE)
	{
		if (vec->index < vec->size || ft_resize_vector(vec))
			vec->u_ptr.p[vec->index++] = *((t_projectile *)u_ptr);
	}
	else if (vec->type == SPRITE)
	{
		if (vec->index < vec->size || ft_resize_vector(vec))
			vec->u_ptr.s[vec->index++] = *((t_sprite *)u_ptr);
	}
	else if (vec->type == HIT)
	{
		if (vec->index < vec->size || ft_resize_vector(vec))
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
