/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditioner1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel-sol <adel-sol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 13:03:31 by adel-sol          #+#    #+#             */
/*   Updated: 2021/02/25 10:51:19 by adel-sol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		m_wall(char x)
{
	if (x == '1' || x == '~')
		return (TRUE);
	return (FALSE);
}

int		m_white_space(char x)
{
	if ((x >= 9 && x <= 13) || x == 32)
		return (TRUE);
	return (FALSE);
}

int		m_fixed_chars(char x)
{
	if (x == '1' || x == ' ')
		return (TRUE);
	return (FALSE);
}

int		m_sp_nl(char x)
{
	if (x == ' ' || x == 0)
		return (TRUE);
	return (FALSE);
}

int		m_player_pos(char x)
{
	if (x == 'N' || x == 'S' || x == 'E' || x == 'W')
		return (TRUE);
	return (FALSE);
}
