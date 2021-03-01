/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_checks.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel-sol <adel-sol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 08:45:43 by adel-sol          #+#    #+#             */
/*   Updated: 2021/02/26 10:18:08 by adel-sol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		set_image(t_mlx *mlx, t_img *img, char *path)
{
	if (!(img->img = mlx_xpm_file_to_image(mlx->ptr, path, \
	&img->width, &img->height)) || !(img->data = \
	(int*)mlx_get_data_addr(img->img, &mlx->pixel_bits, \
	&mlx->line_bytes, &mlx->endian)))
		return (ERROR);
	return (SUCCESS);
}

void	print_matrix(t_config *cfg)
{
	int		i;
	int		j;

	i = 0;
	while (i < cfg->map.height)
	{
		j = 0;
		while (j < cfg->map.width)
		{
			if (j == 0)
				printf("{ ");
			if (j < cfg->map.width - 1)
				printf("'%c', ", cfg->map.content[i][j]);
			else
				printf("'%c' }\n", cfg->map.content[i][j]);
			j++;
		}
		i++;
	}
}

int		char_circle_check(t_config *cfg, t_idx c)
{
	if (check_existing_object(cfg, c) == ERROR)
		return (ERROR);
	if (c.i == 0 || c.j == 0 || c.i == cfg->map.height - 1)
		return (ERROR);
	if (c.i > 0 && c.j > 0 && m_sp_nl(cfg->map.content[c.i - 1][c.j - 1]))
		return (ERROR);
	if (c.i > 0 && (m_sp_nl(cfg->map.content[c.i - 1][c.j]) ||
	m_sp_nl(cfg->map.content[c.i - 1][c.j + 1])))
		return (ERROR);
	if (c.j > 0 && (m_sp_nl(cfg->map.content[c.i][c.j - 1]) ||
	m_sp_nl(cfg->map.content[c.i][c.j + 1])))
		return (ERROR);
	if (c.j > 0 && c.i < cfg->map.height - 1 &&
	m_sp_nl(cfg->map.content[c.i + 1][c.j - 1]))
		return (ERROR);
	if (c.i < cfg->map.height - 1 && (m_sp_nl(cfg->map.content[c.i + 1][c.j])
	|| m_sp_nl(cfg->map.content[c.i + 1][c.j + 1])))
		return (ERROR);
	return (SUCCESS);
}

int		set_player_pos(t_config *cfg, int i, int j)
{
	if (cfg->map.content[i][j] == 'N')
		cfg->player.ang.x = M_PI;
	else if (cfg->map.content[i][j] == 'S')
		cfg->player.ang.x = 0;
	else if (cfg->map.content[i][j] == 'E')
		cfg->player.ang.x = -M_PI / 2;
	else if (cfg->map.content[i][j] == 'W')
		cfg->player.ang.x = M_PI / 2;
	cfg->player.pos.x = (float)j + 0.5;
	cfg->player.pos.y = (float)i + 0.5;
	cfg->player.pos.z = 0.5;
	cfg->base.x = 0;
	cfg->base.y = 1;
	cfg->base.z = 0;
	cfg->player.life = 1;
	cfg->player.poisoned = FALSE;
	return (SUCCESS);
}

int		valid_map_check(t_config *config, int single_player)
{
	t_idx	c;

	c.i = 0;
	while (c.i < config->map.height)
	{
		c.j = 0;
		while (c.j < config->map.width)
		{
			if (m_player_pos(config->map.content[c.i][c.j]))
				single_player += set_player_pos(config, c.i, c.j);
			if (!m_fixed_chars(config->map.content[c.i][c.j]))
				if (char_circle_check(config, c) == ERROR)
					return (print_error("The map is invalid.\n"));
			c.j++;
		}
		c.i++;
	}
	if (single_player != 1)
		return (print_error("The map doesn't have a single player.\n"));
	return (SUCCESS);
}
