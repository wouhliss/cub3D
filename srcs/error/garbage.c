/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wouhliss <wouhliss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 15:01:45 by ybelatar          #+#    #+#             */
/*   Updated: 2024/03/17 17:07:33 by wouhliss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_garbage	*ft_lstnew(void *content)
{
	t_garbage	*lst;

	lst = malloc(sizeof(t_garbage));
	if (!lst)
		return (free(content), NULL);
	lst->content = content;
	lst->next = NULL;
	return (lst);
}

t_garbage	*ft_lstlastt(t_garbage *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

t_garbage	*ft_lstadd_back(t_garbage **lst, t_garbage *new)
{
	t_garbage	*last;

	if (!new)
		return (NULL);
	if (lst)
	{
		if (*lst)
		{
			last = ft_lstlastt(*lst);
			last->next = new;
		}
		else
			*lst = new;
	}
	return (new);
}

void	ft_lstclear_gb(t_garbage **lst)
{
	t_garbage	*tmp;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->content);
		free(*lst);
		*lst = tmp;
	}
}

void	*gc(void *ptr, int i)
{
	static t_garbage	*gb = NULL;

	if (i)
	{
		if (!ft_lstadd_back(&gb, ft_lstnew(ptr)))
			return (NULL);
		return (ptr);
	}
	else
	{
		ft_lstclear_gb(&gb);
		return (NULL);
	}
}
