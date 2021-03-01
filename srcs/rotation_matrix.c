/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_matrix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel-sol <adel-sol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 09:24:28 by adel-sol          #+#    #+#             */
/*   Updated: 2021/02/23 10:25:59 by adel-sol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_point	rot_z(t_point sov, double a, t_config *cfg)
{
	t_point	res;
	int		idx;
	int		neg;

	neg = 1;
	if (a < 0)
		neg = -1;
	idx = abs((int)(a * 10000) % 62831);
	res.x = sov.x * cfg->cos_load[idx] - sov.y * (cfg->sin_load[idx] * neg);
	res.y = sov.x * (cfg->sin_load[idx] * neg) + sov.y * cfg->cos_load[idx];
	res.z = sov.z;
	return (res);
}
