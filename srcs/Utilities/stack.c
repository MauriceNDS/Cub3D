/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel-sol <adel-sol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 14:30:57 by adel-sol          #+#    #+#             */
/*   Updated: 2021/02/23 09:37:26 by adel-sol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		stack_sort(t_stack *stk)
{
	int		i;
	int		j;
	t_elem	temp;

	i = stk->current;
	while (--i > 0)
	{
		j = i;
		while (--j >= 0)
		{
			if (stk->sprites[j].z > stk->sprites[j + 1].z)
			{
				temp = stk->sprites[j + 1];
				stk->sprites[j + 1] = stk->sprites[j];
				stk->sprites[j] = temp;
			}
		}
	}
}

int			stack_push(t_stack *stk, t_elem elem)
{
	stk->sprites[stk->current] = elem;
	stk->current++;
	return (stk->current);
}

t_elem		stack_pop(t_stack *stk)
{
	stk->current--;
	return (stk->sprites[stk->current]);
}

t_elem		stack_head(t_stack *stk)
{
	return (stk->sprites[stk->current]);
}

int			stack_isempty(t_stack stk)
{
	if (stk.current == 0)
		return (TRUE);
	return (FALSE);
}
