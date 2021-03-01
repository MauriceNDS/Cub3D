/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel-sol <adel-sol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 11:17:24 by adel-sol          #+#    #+#             */
/*   Updated: 2021/02/26 14:40:30 by adel-sol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		do_action(t_config *cfg)
{
	double	speed;

	if (cfg->game_state == GAME_ON)
	{
		speed = SPEED;
		if (cfg->key.squat)
			speed = S_SPEED;
		move_player(cfg, speed);
		rotate_camera(cfg);
		squat(cfg);
	}
	return (SUCCESS);
}

int		ft_close(t_config *cfg, int tofree)
{
	if (tofree >= 5)
		free(cfg->lines.h);
	if (tofree >= 4)
		free(cfg->map.content);
	if (tofree >= 3)
		free(cfg->sin_load);
	if (tofree >= 2)
		free(cfg->cos_load);
	if (tofree >= 1)
		free(cfg);
	if (tofree >= 10)
		exit(0);
	exit(ERROR);
	return (SUCCESS);
}

int		key_press(int keycode, t_config *cfg)
{
	if (keycode == 13)
		cfg->key.up = 1;
	else if (keycode == 1)
		cfg->key.down = 1;
	else if (keycode == 0)
		cfg->key.left = 1;
	else if (keycode == 2)
		cfg->key.right = 1;
	else if (keycode == 126)
		cfg->key.rot_u = 1;
	else if (keycode == 125)
		cfg->key.rot_d = 1;
	else if (keycode == 123)
		cfg->key.rot_l = 1;
	else if (keycode == 124)
		cfg->key.rot_r = 1;
	else if (keycode == 257)
		cfg->key.squat = 1;
	else if (keycode == 53)
		exit(0);
	return (SUCCESS);
}

int		key_release(int keycode, t_config *cfg)
{
	if (keycode == 13)
		cfg->key.up = 0;
	else if (keycode == 1)
		cfg->key.down = 0;
	else if (keycode == 0)
		cfg->key.left = 0;
	else if (keycode == 2)
		cfg->key.right = 0;
	else if (keycode == 126)
		cfg->key.rot_u = 0;
	else if (keycode == 125)
		cfg->key.rot_d = 0;
	else if (keycode == 123)
		cfg->key.rot_l = 0;
	else if (keycode == 124)
		cfg->key.rot_r = 0;
	else if (keycode == 257)
		cfg->key.squat = 0;
	return (SUCCESS);
}
