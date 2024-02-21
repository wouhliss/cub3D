/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 21:11:57 by ybelatar          #+#    #+#             */
/*   Updated: 2024/02/21 15:09:48 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	skip_spaces(char *line, int *i)
{
	while (line[*i] == ' ' || (line[*i] >= 9 && line[*i] <= 13))
		(*i)++;
}

int	ft_atoc(const char *str)
{
	int	nb;
	int	sign;

	nb = 0;
	sign = 1;
	while (*str && (*str == ' ' || (*str >= 9 && *str <= 13)))
		++str;
	if (*str && (*str == '-' || *str == '+'))
	{
		if (*str == '-')
			sign = -1;
		++str;
	}
	while (*str && *str >= '0' && *str <= '9')
	{
		if (nb > __UINT8_MAX__)
			return (__UINT8_MAX__ + 1);
		nb = nb * 10 + *str - '0';
		++str;
	}
	return (nb * sign);
}

int	max(int a, int b)
{
	if (a < b)
		return (b);
	else
		return (a);
}
