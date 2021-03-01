/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_interaction.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel-sol <adel-sol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 09:05:08 by adel-sol          #+#    #+#             */
/*   Updated: 2021/02/25 12:46:02 by adel-sol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		get_poisoned(t_config *cfg, int x, int y)
{
	cfg->map.content[y][x] = 0;
	if (cfg->player.poisoned != TRUE)
		cfg->player.poisoned = TRUE;
	else
	{
		cfg->player.life -= 2 * DMG;
		if (cfg->player.life <= 0)
			game_over(cfg);
	}
}

void		restore_hp(t_config *cfg, int x, int y)
{
	cfg->map.content[y][x] = 0;
	if (cfg->player.life + HEAL <= 1)
		cfg->player.life += HEAL;
	else
		cfg->player.life = 1;
}

void		antidote(t_config *cfg, int x, int y)
{
	cfg->map.content[y][x] = 0;
	if (cfg->player.poisoned == TRUE)
		cfg->player.poisoned = FALSE;
}

int			colision(t_config *cfg, float x, float y)
{
	int		ix;
	int		iy;

	ix = x;
	iy = y;
	if (m_solid_sprite(cfg->map.content[iy][ix]) && \
	x - ix >= 0.3 && x - ix <= 0.7 && y - iy >= 0.3 && y - iy <= 0.7)
		return (TRUE);
	if (cfg->map.content[iy][ix] == MUSHROOM && \
	x - ix >= 0.1 && x - ix <= 0.9 && y - iy >= 0.1 && y - iy <= 0.9)
		get_poisoned(cfg, ix, iy);
	if (cfg->map.content[iy][ix] == FINISH && \
	x - ix >= 0.2 && x - ix <= 0.8 && y - iy >= 0.2 && y - iy <= 0.8)
		end_game(cfg);
	if (cfg->map.content[iy][ix] == HEART && \
	x - ix >= 0.2 && x - ix <= 0.8 && y - iy >= 0.2 && y - iy <= 0.8)
		restore_hp(cfg, ix, iy);
	if (cfg->map.content[iy][ix] == ANTIDOTE && \
	x - ix >= 0.2 && x - ix <= 0.8 && y - iy >= 0.2 && y - iy <= 0.8)
		antidote(cfg, ix, iy);
	return (cfg->map.content[iy][ix] == '1');
}
