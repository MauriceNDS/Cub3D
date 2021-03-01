/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel-sol <adel-sol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 08:50:07 by adel-sol          #+#    #+#             */
/*   Updated: 2021/02/26 15:22:07 by adel-sol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		set_resolution(char *line, t_config *cfg)
{
	int		width;
	int		height;

	if (cfg->resolution.check++ == 1)
		return (print_error("Duplicate resolution.\n"));
	if ((width = ft_atoi(line)) < 1 || width > 2560)
		width = 2560;
	while (m_white_space(*line))
		line++;
	while (!m_white_space(*line) && *line != '\0')
		line++;
	if (*line == '\0')
		return (print_error("Invalid resolution.\n"));
	if ((height = ft_atoi(line)) < 1 || height > 1395)
		height = 1395;
	cfg->resolution.x = width;
	cfg->resolution.y = height;
	cfg->mlx.line_bytes = cfg->resolution.y * 4;
	return (SUCCESS);
}

char	*get_texture(char *line)
{
	int		start;
	int		len;
	char	*texture;

	if (*line == '\0')
		return (NULL);
	start = skip_spaces(line);
	len = 0;
	while (!m_white_space(line[start + len]) && line[start + len])
	{
		if (!ft_isalnum(line[start + len]) && line[start + len] != '.'
		&& line[start + len] != '/' && line[start + len] != '-'
		&& line[start + len] != '_' && line[start + len] != '+')
			return (NULL);
		len++;
	}
	if (line[start + len - 4] != '.' && line[start + len - 3] != 'x'
	&& line[start + len - 2] != 'p' && line[start + len - 1] != 'm')
		return (NULL);
	if (!(texture = malloc(len + 1)))
		return (NULL);
	*texture = '\0';
	ft_strlcpy(texture, &line[start], len + 1);
	return (texture);
}

int		set_texture(char *line, char orient, t_config *cfg, int *count)
{
	char	*path;
	int		n;

	n = 0;
	if (*(line - 1) == 'S' && *line > 48 && *line < 56)
		n = *(++line - 1) - 48;
	if (check_duplicate_textures(cfg, orient, n) == ERROR)
		return (ERROR);
	if (!(path = get_texture(line)))
		return (print_error("Invalid texture.\n"));
	if ((orient == 'N' &&
	set_image(&(cfg->mlx), &cfg->textures.north, path) == ERROR) || \
	(orient == 'S' &&
	set_image(&(cfg->mlx), &cfg->textures.south, path) == ERROR) || \
	(orient == 'E' &&
	set_image(&(cfg->mlx), &cfg->textures.east, path) == ERROR) || \
	(orient == 'W' &&
	set_image(&(cfg->mlx), &cfg->textures.west, path) == ERROR))
		return (print_error("Can't get img pointer and adresses.\n"));
	else if (orient == 'Z' && --(*count) != -2 &&
	set_image(&(cfg->mlx), &cfg->textures.sprite[n], path) == ERROR)
		return (print_error("Can't get img pointer and adresses.\n"));
	free(path);
	return (SUCCESS);
}

int		set_fc_color(char *line, char fc, t_config *cfg)
{
	char			**splt;
	unsigned char	color[3];
	int				i;

	if ((fc == 'F' && cfg->check_f++ == 1) || (fc == 'C' && \
	cfg->check_c++ == 1))
		return (print_error("Duplicate color.\n"));
	splt = ft_split(line, ',');
	if (count_split_elems(splt) < 3)
		return (print_error("Wrong color format.\n"));
	i = -1;
	while (++i < 3)
		color[i] = ft_atoi(splt[i]);
	i = -1;
	while (splt[++i])
		free(splt[i]);
	free(splt);
	if (fc == 'F')
	{
		cfg->floor = create_trgb(0, color[0], color[1], color[2]);
		return (SUCCESS);
	}
	cfg->ceiling = create_trgb(0, color[0], color[1], color[2]);
	return (SUCCESS);
}

int		set_animation(char *line, t_config *cfg, int count)
{
	char	*path;
	int		n;

	n = *(++line - 1) - 49;
	if (!(path = get_texture(line)))
		return (print_error("Invalid animation frame.\n"));
	if (cfg->animation[n].f_num >= MAX_FRME)
		return (print_error("Too much frames for the animation!\n"));
	if (set_image(&(cfg->mlx), \
	&cfg->animation[n].frame[cfg->animation[n].f_num], path) == ERROR)
		return (print_error("Can't get img pointer and adresses.\n"));
	cfg->animation[n].f_num++;
	(void)count;
	free(path);
	return (SUCCESS);
}
