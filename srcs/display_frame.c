/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_frame.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel-sol <adel-sol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 15:24:09 by adel-sol          #+#    #+#             */
/*   Updated: 2021/03/01 12:54:29 by adel-sol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		wall_sizer(t_point *wall, t_config *cfg, t_point pixel)
{
	pixel.z *= 2;
	pixel.z *= cos(-(cfg->angle.vis_h) * 0.5 + cfg->ray_idx * cfg->angle.h);
	if (pixel.z == cfg->resolution.x)
		pixel.z += 0.01;
	wall->x = (cfg->resolution.y * 0.5) - (cfg->resolution.x / pixel.z);
	wall->y = (cfg->resolution.y * 0.5) + (cfg->resolution.x / pixel.z);
	wall->x += cfg->bmth;
	wall->y += cfg->bmth;
}

void		double_print(int res_width, int *image, int color)
{
	*image = color;
	if (res_width >= 1000)
		*(image + 1) = color;
	if (res_width >= 1500)
		*(image + 2) = color;
	if (res_width >= 2000)
		*(image + 3) = color;
	if (res_width >= 2500)
		*(image + 4) = color;
	if (res_width >= 3000)
		*(image + 5) = color;
}

void		texture_pixel(t_config *cfg, t_point wall, t_point insec, t_idx a)
{
	int		tx;
	int		ty;
	t_img	texture;

	if (cfg->player.pos.x >= insec.x && insec.x == (int)insec.x)
		texture = cfg->textures.west;
	else if (cfg->player.pos.x < insec.x && insec.x == (int)insec.x)
		texture = cfg->textures.east;
	else if (cfg->player.pos.y >= insec.y && insec.y == (int)insec.y)
		texture = cfg->textures.north;
	else
		texture = cfg->textures.south;
	ty = (a.i - wall.x) * texture.height / (wall.y - wall.x);
	tx = (insec.x - (int)insec.x) * texture.width;
	if (insec.x == (int)insec.x)
		tx = (insec.y - (int)insec.y) * texture.width;
	if (a.i < wall.x)
		double_print(cfg->resolution.x, &cfg->im_data[(a.i * \
		cfg->resolution.x) + a.j], cfg->ceiling);
	else if (a.i > wall.y)
		double_print(cfg->resolution.x, &cfg->im_data[(a.i * \
		cfg->resolution.x) + a.j], cfg->floor);
	else
		double_print(cfg->resolution.x, &cfg->im_data[(a.i * \
		cfg->resolution.x) + a.j], texture.data[(ty * texture.width) + tx]);
}

void		put_pixel(t_config *cfg, t_point vec, t_stack *stk)
{
	t_point		insec;
	t_point		wall;
	t_idx		a;

	insec = wall_intersection(cfg, vec, stk);
	wall_sizer(&wall, cfg, insec);
	a.i = 0;
	a.j = cfg->ray_idx;
	while (a.i < cfg->resolution.y)
	{
		texture_pixel(cfg, wall, insec, a);
		a.i++;
	}
	print_sprites(cfg, stk, a, insec);
}

int			print_frame(t_config *cfg)
{
	int			x;
	t_point		vec;
	t_stack		stk;

	if (!(stk.sprites = malloc(sizeof(t_elem) * (cfg->map.height \
	+ cfg->map.width + 5))))
		return (ERROR);
	pre_frame_setup(cfg, &stk, &x);
	while (x < cfg->resolution.x)
	{
		vec = rot_z(cfg->base, -(cfg->angle.vis_h) * 0.5 + x * \
		cfg->angle.h + cfg->player.ang.x, cfg);
		vec.x += cfg->player.pos.x;
		vec.y += cfg->player.pos.y;
		cfg->ray_idx = x++;
		put_pixel(cfg, vec, &stk);
		if (cfg->resolution.x >= 1000)
			x += (cfg->resolution.x - 500) / 500;
	}
	free(stk.sprites);
	print_hud(cfg);
	mlx_put_image_to_window(cfg->mlx.ptr, cfg->mlx.win, cfg->img, 0, 0);
	timer_tick(cfg);
	return (SUCCESS);
}
