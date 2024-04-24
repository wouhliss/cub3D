/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybelatar <ybelatar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 23:48:10 by ybelatar          #+#    #+#             */
/*   Updated: 2024/04/24 23:49:36 by ybelatar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

bool	ft_valid_color(const char *str)
{
	while (*str)
	{
		if (*str == ',' && *(str + 1) == ',')
			return (false);
		++str;
	}
	return (true);
}
