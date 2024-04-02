/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 16:41:48 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/02 09:43:03 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static inline t_door	*ft_newdoor(t_intvec pos)
{
	t_door		*new;

	new = malloc(sizeof(t_door));
	if (!new)
		return (NULL);
	new->pos = pos;
	new->state = CLOSED;
	new->frame = 0.0;
	new->next = NULL;
	return (new);
}

void	ft_doorsclear(t_game *game)
{
	t_door	*el;
	t_door	*temp;

	el = game->doors;
	while (el)
	{
		temp = el->next;
		free(el);
		el = temp;
	}
}

t_door	*ft_adddoor(t_game *game, t_intvec pos)
{
	t_door	*new;
	t_door	*el;

	new = ft_newdoor(pos);
	if (!new)
		return (NULL);
	if (!game->doors)
	{
		game->doors = new;
		return (new);
	}
	el = game->doors;
	while (el->next)
		el = el->next;
	el->next = new;
	return (new);
}
