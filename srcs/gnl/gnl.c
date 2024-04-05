/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:23:12 by wouhliss          #+#    #+#             */
/*   Updated: 2024/04/05 11:46:12 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_align(t_buffer *buffer)
{
	int	i;

	if (buffer->size == buffer->pos)
	{
		buffer->line = 0;
		buffer->size = 0;
		return ;
	}
	i = 0;
	while (i + buffer->pos < buffer->size)
	{
		buffer->line[i] = buffer->line[i + buffer->pos];
		++i;
	}
	buffer->size = i;
}

char	*ft_strndup(t_buffer *buffer)
{
	char	*res;
	int		i;

	res = malloc(buffer->pos + 1);
	if (!res)
	{
		buffer->line = 0;
		buffer->size = 0;
		return (NULL);
	}
	i = 0;
	while (i < buffer->pos - 1)
	{
		res[i] = buffer->line[i];
		++i;
	}
	res[i] = 0;
	ft_align(buffer);
	return (res);
}

char	*ft_strnjoin(t_buffer *buffer)
{
	char	*res;
	int		i;
	int		j;

	res = gc(malloc(buffer->size + buffer->read + 1), ADD);
	if (!res)
		return (NULL);
	i = 0;
	while (i < buffer->size)
	{
		res[i] = buffer->line[i];
		++i;
	}
	j = 0;
	while (j < buffer->read)
	{
		res[i] = buffer->buff[j];
		++i;
		++j;
	}
	res[i] = 0;
	buffer->size = i;
	buffer->line = res;
	return (res);
}

int	read_next_line(int fd, t_buffer *buffer)
{
	if (ft_strnchr(buffer))
		return (1);
	buffer->read = read(fd, buffer->buff, BUFFER_SIZE);
	while (buffer->read > 0)
	{
		if (!ft_strnjoin(buffer))
			return (0);
		if (ft_strnchr(buffer))
			return (1);
		buffer->read = read(fd, buffer, BUFFER_SIZE);
	}
	if (buffer->read < 0)
		return (0);
	buffer->pos = buffer->size;
	return (2);
}

char	*get_next_line(int fd)
{
	static t_buffer	buffer;
	int				i;

	if (fd == EMPTY_BUFFER)
	{
		buffer.line = 0;
		buffer.size = 0;
		return (NULL);
	}
	i = read_next_line(fd, &buffer);
	if (!i)
	{
		buffer.line = 0;
		buffer.size = 0;
		return (NULL);
	}
	else if (i == 1)
		return (ft_strndup(&buffer));
	else if (i == 2 && buffer.size)
		return (ft_strndup(&buffer));
	return (NULL);
}
