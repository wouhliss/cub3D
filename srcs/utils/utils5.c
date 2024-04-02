/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 07:13:46 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/01 16:50:44 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_outside(const t_game *game, const int x, const int y)
{
	return (x < 1 || x >= game->width - 1 || y < 1 || y >= game->length - 1);
}
