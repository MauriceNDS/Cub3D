/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_setter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel-sol <adel-sol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 09:13:25 by adel-sol          #+#    #+#             */
/*   Updated: 2021/02/25 09:17:05 by adel-sol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	pre_frame_setup(t_config *cfg, t_stack *stk, int *x)
{
	stk->current = 0;
	*x = 0;
	if ((cfg->a_frame += FRME_FREQ) > 10000)
		cfg->a_frame = 0;
	cfg->player.sov = rot_z(cfg->base, cfg->player.ang.x, cfg);
}

void	init_main_img(t_config *cfg)
{
	cfg->img = mlx_new_image(cfg->mlx.ptr, cfg->resolution.x, \
	cfg->resolution.y);
	cfg->im_data = (int*)mlx_get_data_addr(cfg->img, &cfg->mlx.pixel_bits, \
	&cfg->mlx.line_bytes, &cfg->mlx.endian);
	time(&cfg->rawtime);
	cfg->game_time = 0;
	cfg->secc = cfg->rawtime;
}

int		cos_sin_load(t_config *cfg)
{
	int i;

	i = 0;
	if (!(cfg->cos_load = malloc(sizeof(double) * 62831)))
		return (ft_close(cfg, 1));
	if (!(cfg->sin_load = malloc(sizeof(double) * 62831)))
		return (ft_close(cfg, 2));
	while (i < 62831)
	{
		cfg->cos_load[i] = cos(i * 0.0001);
		cfg->sin_load[i] = sin(i * 0.0001);
		i++;
	}
	return (SUCCESS);
}

t_point	get_vec(t_point first, t_point second)
{
	t_point		vec;

	vec.x = second.x - first.x;
	vec.y = second.y - first.y;
	return (vec);
}
