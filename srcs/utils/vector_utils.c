/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 00:57:58 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/16 01:03:47 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	*ft_resize_dvector(t_vector *vector)
{
	t_door	*res;
	size_t	i;
	size_t	j;

	res = ft_calloc(vector->size * 2, vector->bsize);
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
	free(vector->u_ptr.d);
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

	res = ft_calloc(vector->size * 2, vector->bsize);
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
	free(vector->u_ptr.p);
	vector->u_ptr.p = res;
	vector->size *= 2;
	vector->index = j;
	return (res);
}

void	*ft_resize_svector(t_vector *vector)
{
	t_sprite	*res;
	size_t		i;
	size_t		j;

	res = ft_calloc(vector->size * 2, vector->bsize);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (i < vector->index)
	{
		if (!vector->u_ptr.s[i].delete)
			res[j++] = vector->u_ptr.s[i];
		++i;
	}
	free(vector->u_ptr.s);
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

	res = ft_calloc(vector->size * 2, vector->bsize);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	while (i < vector->index)
	{
		if (!vector->u_ptr.h[i].delete)
			res[j++] = vector->u_ptr.h[i];
		++i;
	}
	free(vector->u_ptr.h);
	vector->u_ptr.h = res;
	vector->size *= 2;
	vector->index = j;
	return (res);
}
