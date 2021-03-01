/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_all_params.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel-sol <adel-sol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 10:24:02 by adel-sol          #+#    #+#             */
/*   Updated: 2021/02/26 09:13:03 by adel-sol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		parsing_forest(char *line, int i, t_config *cfg, int *count)
{
	int		ret;

	if (line[i] == 'R')
		ret = set_resolution(&line[i + 1], cfg);
	else if (line[i] == 'N' && line[i + 1] == 'O')
		ret = set_texture(&line[i + 2], 'N', cfg, count);
	else if (line[i] == 'S' && line[i + 1] == 'O')
		ret = set_texture(&line[i + 2], 'S', cfg, count);
	else if (line[i] == 'W' && line[i + 1] == 'E')
		ret = set_texture(&line[i + 2], 'W', cfg, count);
	else if (line[i] == 'E' && line[i + 1] == 'A')
		ret = set_texture(&line[i + 2], 'E', cfg, count);
	else if ((line[i] == 'S' && line[i + 1] > 48 && line[i + 1] < 56) || \
	(line[i] == 'S' && ++(*count)))
		ret = set_texture(&line[i + 1], 'Z', cfg, count);
	else if (line[i] == 'A' && line[i + 1] > 48 && line[i + 1] < 61)
		ret = set_animation(&line[i + 1], cfg, (*count)--);
	else if (line[i] == 'F' || line[i] == 'C')
		ret = set_fc_color(&line[i + 1], line[i], cfg);
	else
		return (print_error("Encountered unkown element during parsing.\n"));
	return (ret);
}

int		read_params(char *line, t_line **map, t_config *cfg, int count)
{
	int		ret;
	int		i;
	char	check;

	ret = 1;
	while (ret != 0 && (ret = get_next_line(cfg->fd, &line)) >= 0)
	{
		i = skip_spaces(line);
		if (!line[i])
		{
			free(line);
			check = INTERUPT;
			continue;
		}
		if (count++ <= 7 || (line[i] == 'A' && line[i + 2] > 48 && \
		line[i + 2] < 61))
		{
			if (parsing_forest(line, i, cfg, &count) == ERROR)
				return (ERROR);
		}
		else if (get_map(line, map, &check) == ERROR)
			return (ERROR);
		free(line);
	}
	return ((ret == ERROR) ? print_error("Can't read from file.\n") : SUCCESS);
}

void	init_config_vals(t_config *cfg)
{
	cfg->angle.vis_h = M_PI / 4;
	cfg->angle.vis_v = M_PI / 4;
	cfg->angle.h = cfg->angle.vis_h / (cfg->resolution.x);
	cfg->angle.v = cfg->angle.vis_v / (cfg->resolution.y);
	cfg->bmth = 0;
	cfg->a_frame = -FRME_FREQ;
	cfg->key.rot_d = 0;
	cfg->key.down = 0;
	cfg->key.left = 0;
	cfg->key.right = 0;
	cfg->key.rot_l = 0;
	cfg->key.rot_r = 0;
	cfg->key.rot_u = 0;
	cfg->key.squat = 0;
	cfg->key.up = 0;
	cfg->game_state = GAME_ON;
}

int		config_params(t_line **map, t_config *cfg)
{
	char	*line;

	cfg->resolution.x = 0;
	line = NULL;
	init_params(cfg);
	if (read_params(line, map, cfg, 0) == ERROR
	|| !cfg->resolution.x)
		return (ERROR);
	if (check_minimum_data(cfg) == ERROR)
		return (ERROR);
	init_config_vals(cfg);
	if (get_life_bar(cfg) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int		parse_all_params(char *file_path, t_config *cfg)
{
	t_line		*map;

	map = NULL;
	if (check_cub_extension(file_path) == ERROR)
		return (print_error("The map extention is not *.cub\n"));
	if ((cfg->fd = open(file_path, O_RDONLY)) == ERROR)
		return (print_error("Can't open the parsing file.\n"));
	if (config_params(&map, cfg) == ERROR)
		return (ERROR);
	if (save_map(map, cfg) == ERROR)
		return (ERROR);
	close(cfg->fd);
	return (SUCCESS);
}
