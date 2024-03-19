/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 21:11:57 by ybelatar          #+#    #+#             */
/*   Updated: 2024/03/16 11:08:28 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	skip_spaces(char *line, int *i)
{
	while (line[*i] == ' ' || (line[*i] >= 9 && line[*i] <= 13))
		(*i)++;
}

void	my_mlx_pixel_put(t_screen *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->ll + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
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

int	ft_strnchr(t_buffer *buffer)
{
	int	i;

	if (!buffer->line)
		return (0);
	i = buffer->resume;
	while (i < buffer->size)
	{
		if (buffer->line[i] == '\n')
		{
			buffer->pos = i + 1;
			return (1);
		}
		++i;
	}
	buffer->resume = i;
	return (0);
}
