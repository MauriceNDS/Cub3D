/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_last_frame.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel-sol <adel-sol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 09:10:05 by adel-sol          #+#    #+#             */
/*   Updated: 2021/02/25 09:12:16 by adel-sol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		final_score(t_config *cfg)
{
	char	*t;
	char	*tmp;
	char	*all;

	t = ft_itoa(cfg->game_time / 60);
	all = ft_strjoin("Your final score is - ", t);
	free(t);
	tmp = ft_strjoin(all, " m ");
	free(all);
	t = ft_itoa(cfg->game_time % 60);
	all = ft_strjoin(tmp, t);
	free(t);
	free(tmp);
	tmp = ft_strjoin(all, " s.");
	mlx_string_put(cfg->mlx.ptr, cfg->mlx.win, cfg->resolution.x / 50, \
	cfg->resolution.y / 50, 0x000000, tmp);
	free(all);
	free(tmp);
}

int			end_game(t_config *cfg)
{
	t_img	img;
	t_idx	a;
	t_point	ratio;

	cfg->game_state = END_GAME;
	if (!(img.img = mlx_xpm_file_to_image(cfg->mlx.ptr, FINAL_SCENE, \
	&img.width, &img.height)) || !(img.data = (int*)mlx_get_data_addr(img.img,\
	&cfg->mlx.pixel_bits, &cfg->mlx.line_bytes, &cfg->mlx.endian)))
		return (ft_close(cfg, 5));
	ratio.x = (float)img.width / cfg->resolution.x;
	ratio.y = (float)img.height / cfg->resolution.y;
	a.i = 0;
	while (a.i < cfg->resolution.y)
	{
		a.j = -1;
		while (++a.j < cfg->resolution.x)
			cfg->im_data[a.i * cfg->resolution.x + a.j] = img.data[
			(int)(a.i * ratio.y) * img.width + (int)(a.j * ratio.x)];
		a.i++;
	}
	mlx_put_image_to_window(cfg->mlx.ptr, cfg->mlx.win, cfg->img, 0, 0);
	final_score(cfg);
	return (SUCCESS);
}

int			game_over(t_config *cfg)
{
	t_img	img;
	t_idx	a;
	t_point	ratio;

	cfg->game_state = END_GAME;
	if (!(img.img = mlx_xpm_file_to_image(cfg->mlx.ptr, GAME_OVER, \
	&img.width, &img.height)) || !(img.data = (int*)mlx_get_data_addr(img.img,\
	&cfg->mlx.pixel_bits, &cfg->mlx.line_bytes, &cfg->mlx.endian)))
		return (ft_close(cfg, 5));
	ratio.x = (float)img.width / cfg->resolution.x;
	ratio.y = (float)img.height / cfg->resolution.y;
	a.i = 0;
	while (a.i < cfg->resolution.y)
	{
		a.j = -1;
		while (++a.j < cfg->resolution.x)
			cfg->im_data[a.i * cfg->resolution.x + a.j] = img.data[
			(int)(a.i * ratio.y) * img.width + (int)(a.j * ratio.x)];
		a.i++;
	}
	mlx_put_image_to_window(cfg->mlx.ptr, cfg->mlx.win, cfg->img, 0, 0);
	return (SUCCESS);
}
