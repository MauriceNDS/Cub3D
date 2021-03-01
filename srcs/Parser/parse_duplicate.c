/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_duplicate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel-sol <adel-sol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 13:22:49 by adel-sol          #+#    #+#             */
/*   Updated: 2021/02/25 14:27:26 by adel-sol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		check_existing_object(t_config *cfg, t_idx c)
{
	if (m_s_2_9(cfg->map.content[c.i][c.j]))
	{
		if (cfg->textures.sprite[cfg->map.content[c.i][c.j] - 50].check == 0)
			return (ERROR);
		return (SUCCESS);
	}
	if (m_anim(cfg->map.content[c.i][c.j]))
	{
		if (cfg->animation[cfg->map.content[c.i][c.j] - 97].f_num == 0)
			return (ERROR);
		return (SUCCESS);
	}
	return (SUCCESS);
}

int		check_duplicate_textures(t_config *cfg, char x, int n)
{
	if (x == 'N' && cfg->textures.north.check++ == 1)
		return (print_error("Duplicate texture!\n"));
	if (x == 'S' && cfg->textures.south.check++ == 1)
		return (print_error("Duplicate texture!\n"));
	if (x == 'E' && cfg->textures.east.check++ == 1)
		return (print_error("Duplicate texture!\n"));
	if (x == 'W' && cfg->textures.west.check++ == 1)
		return (print_error("Duplicate texture!\n"));
	if (x == 'Z' && cfg->textures.sprite[n].check++ == 1)
		return (print_error("Duplicate sprite!\n"));
	return (SUCCESS);
}

int		check_minimum_data(t_config *cfg)
{
	if (cfg->resolution.check != 1 || cfg->textures.north.check != 1 || \
	cfg->textures.south.check != 1 || cfg->textures.east.check != 1 || \
	cfg->textures.west.check != 1 || cfg->textures.sprite[0].check != 1 || \
	cfg->check_f != 1 || cfg->check_c != 1)
		return (print_error("Minimum required data missing.\n"));
	return (SUCCESS);
}
