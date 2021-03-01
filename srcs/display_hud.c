/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_hud.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel-sol <adel-sol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 09:08:23 by adel-sol          #+#    #+#             */
/*   Updated: 2021/02/26 09:13:34 by adel-sol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		print_timer_bg(t_config *cfg)
{
	t_idx	a;

	a.i = -1;
	while (++a.i < cfg->resolution.y / 35)
	{
		a.j = cfg->resolution.x - cfg->resolution.x / 15 - 1;
		while (++a.j < cfg->resolution.x)
			cfg->im_data[a.i * cfg->resolution.x + a.j] = BORDER_HUD;
	}
}

int			poisoned_color(int color)
{
	if (color == RED_1)
		return (PURPLE_1);
	else if (color == RED_2)
		return (PURPLE_2);
	else if (color == RED_3)
		return (PURPLE_3);
	else if (color == RED_4)
		return (PURPLE_4);
	return (color);
}

void		print_hud(t_config *cfg)
{
	t_idx	a;
	t_img	bar;
	t_point	r;
	int		color;

	if (cfg->player.life <= 0 && game_over(cfg))
		return ;
	bar = cfg->textures.life_bar[(int)round(LIFE_NUM * cfg->player.life) - 1];
	r.x = (float)bar.width / (cfg->resolution.x / 4);
	r.y = (float)bar.height / (cfg->resolution.y / 20);
	a.i = -1;
	while (++a.i < cfg->resolution.y / 20)
	{
		a.j = -1;
		while (++a.j < cfg->resolution.x / 4)
		{
			color = bar.data[(int)(a.i * r.y) * bar.width + (int)(a.j * r.x)];
			if (cfg->player.poisoned == TRUE)
				color = poisoned_color(color);
			if (color != 0xffffff)
				cfg->im_data[a.i * cfg->resolution.x + a.j] = color;
		}
	}
	print_timer_bg(cfg);
}

void		timer_tick(t_config *cfg)
{
	char	*t;
	char	*tmp;
	char	*all;

	time(&cfg->rawtime);
	if (cfg->secc != cfg->rawtime && (cfg->secc = cfg->rawtime))
	{
		cfg->game_time++;
		if (cfg->player.poisoned == TRUE)
		{
			cfg->player.life -= DMG;
			if (cfg->player.life <= 0 && game_over(cfg))
				return ;
		}
	}
	t = ft_itoa(cfg->game_time / 60);
	tmp = ft_strjoin(t, ":");
	free(t);
	t = ft_itoa(cfg->game_time % 60);
	all = ft_strjoin(tmp, t);
	free(t);
	free(tmp);
	mlx_string_put(cfg->mlx.ptr, cfg->mlx.win, cfg->resolution.x - \
	cfg->resolution.x / 25, cfg->resolution.y / 50, 0xFFFFFF, all);
	free(all);
}
