/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 21:11:57 by ybelatar          #+#    #+#             */
/*   Updated: 2024/04/03 18:05:08 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	skip_spaces(char *line, int *i)
{
	while (line[*i] == ' ' || (line[*i] >= 9 && line[*i] <= 13))
		(*i)++;
}

inline void	my_mlx_pixel_put(const t_screen *data, const int x, const int y, const int color)
{
	char	*dst;

	dst = data->addr + (y * data->ll + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

inline void	my_mlx_pixel_tput(const t_screen *data, const int x, const int y, unsigned int color)
{
	char			*dst;
	t_color			tcolor;
	t_color			scolor;
	t_color			dcolor;

	dst = data->addr + (y * data->ll + x * (data->bpp / 8));
	scolor.hex = *(unsigned int *)dst;
	tcolor.hex = color;
	dcolor.t = (0.50 * scolor.t) + (0.50 * tcolor.t);
	dcolor.red = (0.50 * scolor.red) + (0.50 * tcolor.red);
	dcolor.green = (0.50 * scolor.green) + (0.50 * tcolor.green);
	dcolor.blue = (0.50 * scolor.blue) + (0.50 * tcolor.blue);
	*(unsigned int *)dst = dcolor.hex;
}

inline void	my_mlx_pixel_hput(t_screen *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->ll + x * (data->bpp / 8));
	*(unsigned int *)dst = create_trgb((unsigned char)(color >> 24) >> 1,
			(unsigned char)(color >> 16) >> 1, (unsigned char)(color >> 8) >> 1,
			(unsigned char)(color) >> 1);
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
