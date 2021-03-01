/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel-sol <adel-sol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 12:42:43 by adel-sol          #+#    #+#             */
/*   Updated: 2021/02/25 09:00:40 by adel-sol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		free_config(t_config *cfg, int code)
{
	int		i;

	i = -1;
	if (code >= 0)
		free(cfg->lines.h);
	if (code >= 1)
		free(cfg->lines.v);
	while (++i < cfg->map.height)
		free(cfg->map.content[i]);
	free(cfg->map.content);
	return (ERROR);
}

t_point	rot_90(t_point sov)
{
	t_point	res;

	res.x = sov.x * -0.00000367 - sov.y;
	res.y = sov.x + sov.y * -0.00000367;
	res.z = sov.z;
	return (res);
}

double	line_slope(t_point a, t_point b)
{
	if (a.x - b.x == 0.0)
		return (NAN);
	else
		return ((a.y - b.y) / (a.x - b.x));
}

double	two_points_dist(t_point a, t_point b)
{
	return (sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2)));
}

int		build_lines(t_config *cfg)
{
	int		i;

	i = -1;
	cfg->lines.hl = cfg->map.height + 1;
	cfg->lines.vl = cfg->map.width + 1;
	if (!(cfg->lines.h = malloc(sizeof(t_ln) * cfg->lines.hl)))
		return (ft_close(cfg, 4));
	if (!(cfg->lines.v = malloc(sizeof(t_ln) * cfg->lines.vl)))
		return (ft_close(cfg, 5));
	while (++i < cfg->lines.hl)
	{
		cfg->lines.h[i].a.x = 1;
		cfg->lines.h[i].a.y = i;
		cfg->lines.h[i].b.x = 6;
		cfg->lines.h[i].b.y = i;
	}
	i = -1;
	while (++i < cfg->lines.vl)
	{
		cfg->lines.v[i].a.x = i;
		cfg->lines.v[i].a.y = 1;
		cfg->lines.v[i].b.x = i;
		cfg->lines.v[i].b.y = 6;
	}
	return (SUCCESS);
}
