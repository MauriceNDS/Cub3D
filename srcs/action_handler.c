/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel-sol <adel-sol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 09:57:15 by adel-sol          #+#    #+#             */
/*   Updated: 2021/03/01 14:36:45 by adel-sol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		move_up_down(t_config *cfg, double s, t_point sov, t_point *pos)
{
	if (cfg->key.up)
	{
		pos->x = cfg->player.pos.x + sov.x * s;
		pos->y = cfg->player.pos.y + sov.y * s;
	}
	else if (cfg->key.down)
	{
		pos->x = cfg->player.pos.x - sov.x * s;
		pos->y = cfg->player.pos.y - sov.y * s;
	}
}

void		move_left_right(t_config *cfg, double s, t_point sov, t_point *pos)
{
	if (cfg->key.right)
	{
		sov = rot_z(cfg->player.sov, M_PI / 2, cfg);
		pos->x += sov.x * s / 2;
		pos->y += sov.y * s / 2;
	}
	else if (cfg->key.left)
	{
		sov = rot_z(cfg->player.sov, -M_PI / 2, cfg);
		pos->x += sov.x * s / 2;
		pos->y += sov.y * s / 2;
	}
}

void		move_player(t_config *cfg, double speed)
{
	t_point		pos;
	t_point		sov;

	sov = cfg->player.sov;
	pos = cfg->player.pos;
	move_up_down(cfg, speed, sov, &pos);
	move_left_right(cfg, speed, sov, &pos);
	if (!colision(cfg, pos.x, cfg->player.pos.y))
		cfg->player.pos.x = roundf(pos.x * 10000) / 10000;
	if (!colision(cfg, cfg->player.pos.x, pos.y))
		cfg->player.pos.y = roundf(pos.y * 10000) / 10000;
	if (cfg->game_state == GAME_ON)
		print_frame(cfg);
}

void		rotate_camera(t_config *cfg)
{
	if (cfg->key.rot_u && cfg->bmth < cfg->resolution.y)
		cfg->bmth += cfg->resolution.y / 50;
	else if (cfg->key.rot_d && cfg->bmth > -cfg->resolution.y)
		cfg->bmth -= cfg->resolution.y / 50;
	if (cfg->key.rot_l)
		cfg->player.ang.x -= 0.02;
	else if (cfg->key.rot_r)
		cfg->player.ang.x += 0.02;
}

void		squat(t_config *cfg)
{
	static int	count = 0;

	if (cfg->key.squat && !count)
	{
		cfg->bmth -= cfg->resolution.y / 10;
		count++;
	}
	else if (!cfg->key.squat && count)
	{
		cfg->bmth += cfg->resolution.y / 10;
		count--;
	}
}
