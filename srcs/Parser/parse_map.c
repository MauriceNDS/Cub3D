/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel-sol <adel-sol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 14:05:22 by adel-sol          #+#    #+#             */
/*   Updated: 2021/02/26 09:12:45 by adel-sol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		check_map_valid_characters(char *line)
{
	while (*line)
	{
		if (!m_map_valid_characters(*line))
			return (ERROR);
		line++;
	}
	return (SUCCESS);
}

int		get_map(char *line, t_line **map, char *interupt)
{
	t_line	*new_line;

	if (!*map)
		*interupt = 1;
	if (*interupt == INTERUPT)
		return (print_error("The map is severed by an empty line.\n"));
	if (check_map_valid_characters(line) == ERROR)
		return (print_error("Invalid character in map.\n"));
	if (!(new_line = malloc(sizeof(t_line))))
		return (print_error("Can't allocate memory in get_map.\n"));
	new_line->line = ft_strdup(line);
	new_line->len = ft_strlen(new_line->line);
	new_line->next = NULL;
	ft_lst_back(map, new_line);
	return (SUCCESS);
}

int		create_line(char *to, char *from, int len)
{
	int		ret;

	to[0] = '\0';
	if (!(ret = ft_strlcpy(to, from, len + 1)))
		return (ERROR);
	while (ret < len)
		to[ret++] = ' ';
	return (SUCCESS);
}

void	lst_free_elem(t_line *elem)
{
	if (!elem)
		return ;
	free(elem->line);
	free(elem);
}

int		save_map(t_line *map, t_config *config)
{
	t_line	*del;
	int		i;

	config->map.height = ft_sizelst(map);
	if (!(config->map.content = malloc(sizeof(char*) * config->map.height)))
		return (print_error("Can't allocate memory in save_map.\n"));
	i = 0;
	config->map.width = get_max_width(map);
	while (i < config->map.height)
	{
		if (!(config->map.content[i] = malloc(config->map.width + 1)))
			return (free_map_onerr(&(config->map), &map, i));
		if ((create_line(config->map.content[i], map->line,
		config->map.width)) == ERROR)
			return (print_error("Can't copy a line from linked list.\n"));
		i++;
		del = map;
		map = map->next;
		lst_free_elem(del);
	}
	if (valid_map_check(config, 0) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
