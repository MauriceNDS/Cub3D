/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_precision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel-sol <adel-sol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 10:07:28 by adel-sol          #+#    #+#             */
/*   Updated: 2021/02/25 09:18:14 by adel-sol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_sprites_pre_set(t_point *wall, t_elem s, t_config *cfg, t_idx *t)
{
	wall->x = cfg->resolution.y * 0.5 - (cfg->resolution.x / \
	(s.z * 2)) + cfg->bmth;
	wall->y = cfg->resolution.y * 0.5 + (cfg->resolution.x / \
	(s.z * 2)) + cfg->bmth;
	if (s.x > 0)
		t->j = s.s.width * 0.5 + (s.y * 2 * s.s.width);
	else
		t->j = s.s.width * 0.5 - (s.y * 2 * s.s.width);
}

void	print_sprites(t_config *cfg, t_stack *stk, t_idx a, t_point insec)
{
	t_idx		t;
	t_elem		sprite;
	t_point		wall;

	stack_sort(stk);
	while (!stack_isempty(*stk))
	{
		sprite = stack_pop(stk);
		if (sprite.z > insec.z || sprite.z <= 0)
			continue ;
		print_sprites_pre_set(&wall, sprite, cfg, &t);
		a.i = -1;
		while (++a.i < cfg->resolution.y)
		{
			if (a.i < wall.x || a.i >= wall.y)
				continue ;
			t.i = (a.i - wall.x) * sprite.s.height / (wall.y - wall.x);
			sprite_precision(cfg, &a, t, sprite);
		}
	}
}

void	sprite_precision(t_config *cfg, t_idx *a, t_idx t, t_elem sprite)
{
	int		prec;
	int		color;

	if (sprite.z < 1)
		prec = a->i + 4;
	else if (sprite.z < 2)
		prec = a->i + 3;
	else if (sprite.z < 4)
		prec = a->i + 2;
	else
		prec = a->i;
	color = sprite.s.data[t.i * sprite.s.width + abs(t.j) % sprite.s.height];
	if (color == 0x000000 || sprite.y > 0.25)
		return ;
	while (a->i <= prec && a->i < cfg->resolution.y)
		double_print(cfg->resolution.x, &cfg->im_data[a->i++ * \
		cfg->resolution.x + a->j], color);
	a->i--;
}
