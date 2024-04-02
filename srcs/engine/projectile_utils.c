/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectile_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 16:03:19 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/01 16:33:09 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static inline t_projectile	*ft_newprojectile(t_game *game, t_vec pos,
		t_vec dir, int type)
{
	t_projectile	*new;
	t_sprite		sprite;

	new = malloc(sizeof(t_projectile));
	if (!new)
		return (NULL);
	sprite = (t_sprite){.type = 2, .vdiff = 64.0, .hr = 2, .vr = 2, .hide = 0,
		.pos = pos, .t = &game->textures[4], .dir = dir};
	new->sprite = ft_addsprite(game, &sprite);
	new->type = type;
	new->delete = 0;
	new->next = NULL;
	return (new);
}

void	ft_projectilesclear(t_game *game)
{
	t_projectile	*el;
	t_projectile	*temp;

	el = game->projectiles;
	while (el)
	{
		temp = el->next;
		free(el);
		el = temp;
	}
}

t_projectile	*ft_addprojectile(t_game *game, t_vec pos, t_vec dir, int type)
{
	t_projectile	*new;
	t_projectile	*el;

	new = ft_newprojectile(game, pos, dir, type);
	if (!new)
		return (NULL);
	if (!game->projectiles)
	{
		game->projectiles = new;
		return (new);
	}
	el = game->projectiles;
	while (el->next)
		el = el->next;
	el->next = new;
	return (new);
}
