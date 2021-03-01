/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_manager.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel-sol <adel-sol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 12:39:57 by adel-sol          #+#    #+#             */
/*   Updated: 2021/02/23 13:07:07 by adel-sol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		set_x_y(t_point *res, double first, double second)
{
	res->x = first;
	res->y = second;
}

int			intersection(t_config *cfg, t_point a2, t_ln line, t_point *res)
{
	double	slope_a;
	double	slope_b;
	t_point	a1;

	res->z = 0;
	a1 = cfg->player.pos;
	slope_a = line_slope(a1, a2);
	slope_b = line_slope(line.a, line.b);
	if (slope_a == slope_b || (isnan(slope_a) && isnan(slope_b)))
	{
		res->z = NO_INSEC;
		return (ERROR);
	}
	else if (isnan(slope_a) && !isnan(slope_b))
		set_x_y(res, a1.x, (a1.x - line.a.x) * slope_b + line.a.y);
	else if (isnan(slope_b) && !isnan(slope_a))
		set_x_y(res, line.a.x, (line.a.x - a1.x) * slope_a + a1.y);
	else
		set_x_y(res, (slope_a * a1.x - slope_b * line.a.x + line.a.y - a1.y) \
		/ (slope_a - slope_b), slope_b * (res->x - line.a.x) + line.a.y);
	return (SUCCESS);
}

void		set_dif(t_point vec, t_point *dif, t_config *cfg)
{
	if (vec.x >= cfg->player.pos.x)
		dif->x = 1;
	else
		dif->x = -1;
	if (vec.y >= cfg->player.pos.y)
		dif->y = 1;
	else
		dif->y = -1;
	dif->z = 0;
}

t_point		get_closest_insec(t_player pl, t_point horiz, t_point verti)
{
	t_point		hlen;
	t_point		vlen;

	hlen = horiz;
	vlen = verti;
	hlen.z = sqrt(pow((pl.pos.x - hlen.x), 2) + pow((pl.pos.y - hlen.y), 2));
	vlen.z = sqrt(pow((pl.pos.x - vlen.x), 2) + pow((pl.pos.y - vlen.y), 2));
	if (horiz.z == NO_INSEC)
		return (vlen);
	if (verti.z == NO_INSEC)
		return (hlen);
	if (hlen.z < vlen.z)
		return (hlen);
	return (vlen);
}

t_point		wall_intersection(t_config *cfg, t_point vec, t_stack *stk)
{
	t_point	h_insec;
	t_point	v_insec;
	t_point	dif;
	int		i;

	set_dif(vec, &dif, cfg);
	i = (int)cfg->player.pos.y + ((dif.y == 1) ? 1 : 0);
	while (i > 0 && i < cfg->lines.hl &&
	intersection(cfg, vec, cfg->lines.h[i], &h_insec))
	{
		if (!check_insec(&h_insec, cfg, dif, stk) || m_wall(cfg->map.content\
		[(int)h_insec.y - ((dif.y == 1) ? 0 : 1)][(int)h_insec.x]))
			break ;
		i += dif.y;
	}
	i = (int)cfg->player.pos.x + ((dif.x == 1) ? 1 : 0);
	while (i > 0 && i < cfg->lines.vl &&
	intersection(cfg, vec, cfg->lines.v[i], &v_insec))
	{
		if (!check_insec(&v_insec, cfg, dif, stk) || m_wall(cfg->map.content\
		[(int)v_insec.y][(int)v_insec.x - ((dif.x == 1) ? 0 : 1)]))
			break ;
		i += dif.x;
	}
	return (get_closest_insec(cfg->player, h_insec, v_insec));
}
