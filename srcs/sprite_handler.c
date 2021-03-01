/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel-sol <adel-sol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 09:17:49 by adel-sol          #+#    #+#             */
/*   Updated: 2021/02/25 09:18:07 by adel-sol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_elem	sprite_insec(t_point a1, t_point a2, t_point b1, t_point b2)
{
	double	slope_a;
	double	slope_b;
	t_elem	res;

	res.z = 0;
	slope_a = line_slope(a1, a2);
	slope_b = line_slope(b1, b2);
	if (isnan(slope_a) && !isnan(slope_b))
	{
		res.x = a1.x;
		res.y = (a1.x - b1.x) * slope_b + b1.y;
	}
	else if (isnan(slope_b) && !isnan(slope_a))
	{
		res.x = b1.x;
		res.y = (b1.x - a1.x) * slope_a + a1.y;
	}
	else
	{
		res.x = (slope_a * a1.x - slope_b * b1.x + b1.y - a1.y) \
		/ (slope_a - slope_b);
		res.y = slope_b * (res.x - b1.x) + b1.y;
	}
	return (res);
}

int		visible_sprite(t_config *cfg, t_point center)
{
	float	a;
	float	b;
	t_point	check;

	check.x = cfg->player.sov.x + cfg->player.pos.x;
	check.y = cfg->player.sov.y + cfg->player.pos.y;
	a = two_points_dist(check, center);
	check.x = -cfg->player.sov.x + cfg->player.pos.x;
	check.y = -cfg->player.sov.y + cfg->player.pos.y;
	b = two_points_dist(check, center);
	if (a < b)
		return (TRUE);
	return (FALSE);
}

void	sprite_meeting(t_point *insec, t_config *cfg, t_point dif, t_stack *stk)
{
	t_point		center;

	if (m_is_sprite(cfg->map.content[(int)cfg->player.pos.y]\
	[(int)cfg->player.pos.x]) && stk->current < 1)
	{
		center.x = (int)cfg->player.pos.x + 0.5;
		center.y = (int)cfg->player.pos.y + 0.5;
		if (visible_sprite(cfg, center))
			sprite_pixel(center, cfg, *insec, stk);
	}
	if (insec->y == (int)insec->y && m_is_sprite(cfg->map.content \
	[(int)insec->y - ((dif.y == 1) ? 0 : 1)][(int)insec->x]))
	{
		center.x = (int)insec->x + 0.5;
		center.y = (int)insec->y - ((dif.y == 1) ? 0 : 1) + 0.5;
		sprite_pixel(center, cfg, *insec, stk);
	}
	else if (insec->x == (int)insec->x && m_is_sprite(cfg->map.content \
	[(int)insec->y][(int)insec->x - ((dif.x == 1) ? 0 : 1)]))
	{
		center.x = (int)insec->x - ((dif.x == 1) ? 0 : 1) + 0.5;
		center.y = (int)insec->y + 0.5;
		sprite_pixel(center, cfg, *insec, stk);
	}
}

int		check_insec(t_point *insec, t_config *cfg, t_point dif, t_stack *stk)
{
	if (insec->y < 0 || insec->y >= cfg->map.height || insec->x < 0 || \
	insec->x >= cfg->map.width || isnan(insec->y) || isnan(insec->x))
	{
		insec->z = NO_INSEC;
		return (FALSE);
	}
	sprite_meeting(insec, cfg, dif, stk);
	return (TRUE);
}

void	sprite_pixel(t_point center, t_config *cfg, t_point insec, t_stack *stk)
{
	t_point		line;
	t_elem		elem;

	line = get_vec(center, cfg->player.pos);
	line = rot_90(line);
	line.x += center.x;
	line.y += center.y;
	elem = sprite_insec(cfg->player.pos, insec, center, line);
	elem.z = two_points_dist(cfg->player.pos, center);
	elem.y = sqrt(pow((center.x - elem.x), 2) + pow((center.y - elem.y), 2));
	if (center.y < cfg->player.pos.y && elem.x <= center.x)
		elem.x = -1;
	else if (center.y >= cfg->player.pos.y && elem.x >= center.x)
		elem.x = -1;
	if (cfg->map.content[(int)center.y][(int)center.x] - 50 <= 7)
		elem.s = cfg->textures.sprite[cfg->map.content[(int)center.y]\
		[(int)center.x] - 50];
	else
		elem.s = cfg->animation[cfg->map.content[(int)center.y]\
		[(int)center.x] - 97].frame[(int)cfg->a_frame % cfg->animation \
		[cfg->map.content[(int)center.y][(int)center.x] - 97].f_num];
	stack_push(stk, elem);
}
