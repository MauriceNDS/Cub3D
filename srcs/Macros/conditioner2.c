/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditioner2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel-sol <adel-sol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 13:19:55 by adel-sol          #+#    #+#             */
/*   Updated: 2021/03/01 12:58:29 by adel-sol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		m_s_2_9(char x)
{
	if (x == '2' || x == '3' || x == '4' || x == '5' || x == '6' || x == '7' \
	|| x == '8' || x == '9')
		return (TRUE);
	return (FALSE);
}

int		m_anim(char x)
{
	if (x == 'a' || x == 'b' || x == 'c' || x == 'd' || x == 'e')
		return (TRUE);
	return (FALSE);
}

int		m_is_sprite(char x)
{
	if (m_s_2_9(x) || m_anim(x))
		return (TRUE);
	return (FALSE);
}

int		m_solid_sprite(char x)
{
	if (x == '2' || x == '3')
		return (TRUE);
	return (FALSE);
}

int		m_map_valid_characters(char x)
{
	if (x == '0' || x == '1' || m_s_2_9(x) || x == 'N' || x == 'S' \
	|| x == 'E' || x == 'W' || x == ' ' || m_anim(x) || x == '~')
		return (TRUE);
	return (FALSE);
}
