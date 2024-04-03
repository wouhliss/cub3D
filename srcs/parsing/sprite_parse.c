/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 23:40:04 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/03 17:33:30 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static inline t_sprite	*ft_newsprite(t_sprite *sprite)
{
	t_sprite	*new;

	new = gc(malloc(sizeof(t_sprite)), ADD);
	if (!new)
		return (NULL);
	*new = *sprite;
	new->delete = 0;
	new->next = NULL;
	return (new);
}

void	ft_spritesclear(t_game *game)
{
	t_sprite	*el;
	t_sprite	*temp;

	el = game->sprites;
	while (el)
	{
		temp = el->next;
		free(el);
		el = temp;
	}
}

t_sprite	*ft_addsprite(t_game *game, t_sprite *sprite)
{
	t_sprite	*new;
	t_sprite	*el;

	new = ft_newsprite(sprite);
	if (!new)
		return (NULL);
	if (!game->sprites)
	{
		game->sprites = new;
		return (new);
	}
	el = game->sprites;
	while (el->next)
		el = el->next;
	el->next = new;
	return (new);
}
