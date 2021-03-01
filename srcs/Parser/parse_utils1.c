/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel-sol <adel-sol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 16:34:05 by adel-sol          #+#    #+#             */
/*   Updated: 2021/02/25 08:50:32 by adel-sol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_lst_back(t_line **alst, t_line *new)
{
	t_line	*last;

	if (!alst)
		return ;
	if (!*alst)
		*alst = new;
	else
	{
		last = ft_lastlst(*alst);
		last->next = new;
	}
}

t_line	*ft_lastlst(t_line *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

int		ft_sizelst(t_line *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

int		get_max_width(t_line *lst)
{
	int		res;

	res = -1;
	while (lst)
	{
		if (lst->len > res)
			res = lst->len;
		lst = lst->next;
	}
	return (res);
}

int		free_map_onerr(t_map *map, t_line **lines, int i)
{
	int		j;
	t_line	*cpy;

	j = 0;
	while (j < i)
		free(map->content[j++]);
	free(map->content);
	while (*lines)
	{
		cpy = (*lines)->next;
		lst_free_elem(*lines);
		*lines = cpy;
	}
	return (print_error("Can't allocate memory.\n"));
}
