/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel-sol <adel-sol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 08:50:50 by adel-sol          #+#    #+#             */
/*   Updated: 2021/02/25 13:15:44 by adel-sol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		print_error(char *msg)
{
	printf("Error\n%s", msg);
	return (ERROR);
}

int		get_life_bar(t_config *cfg)
{
	int		i;
	char	*path;
	char	*tmp;
	char	*num;

	i = -1;
	while (++i < LIFE_NUM)
	{
		num = ft_itoa(i + 1);
		tmp = ft_strjoin(LIFE_BAR_NAME, num);
		free(num);
		path = ft_strjoin(tmp, ".xpm");
		free(tmp);
		if (set_image(&cfg->mlx, &cfg->textures.life_bar[i], path) == ERROR)
			return (print_error("Can't get img pointer and adresses.\n"));
		free(path);
	}
	return (SUCCESS);
}

int		check_cub_extension(char *path)
{
	int		len;

	len = ft_strlen(path);
	if (len > 4 && path[len - 4] == '.' && path[len - 3] == 'c' \
	&& path[len - 2] == 'u' && path[len - 1] == 'b')
		return (SUCCESS);
	return (ERROR);
}

int		skip_spaces(char *line)
{
	int		index;

	index = 0;
	while (m_white_space(line[index]))
		index++;
	return (index);
}

void	init_params(t_config *cfg)
{
	int	j;

	j = -1;
	while (++j < MAX_ANIM)
		cfg->animation[j].f_num = 0;
	j = -1;
	while (++j < SPRITES)
		cfg->textures.sprite[j].check = 0;
	cfg->textures.north.check = 0;
	cfg->textures.south.check = 0;
	cfg->textures.west.check = 0;
	cfg->textures.east.check = 0;
	cfg->resolution.check = 0;
	cfg->check_c = 0;
	cfg->check_f = 0;
}
