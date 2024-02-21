/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 15:59:33 by ybelatar          #+#    #+#             */
/*   Updated: 2024/02/21 15:42:16 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	panic(const char *message)
{
	ft_dprintf(2, ERR_FORMAT, NAME, message);
	gc(NULL, 0);
	exit(1);
}
