/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 16:41:34 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/01 17:29:25 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_door	*ft_getdoor(const t_game *game, const int x, const int y)
{
	t_door	*el;

	el = game->doors;
	while (el)
	{
		if (el->pos.x == x && el->pos.y == y)
			return (el);
		el = el->next;
	}
	return (NULL);
}
