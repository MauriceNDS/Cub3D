/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_save.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel-sol <adel-sol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 12:17:58 by adel-sol          #+#    #+#             */
/*   Updated: 2021/02/23 09:56:42 by adel-sol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	data_to_bitmap(t_config *cfg, int fd)
{
	int i;
	int j;

	i = cfg->resolution.y - 1;
	while (i >= 0)
	{
		j = 0;
		while (j < cfg->resolution.x)
		{
			write(fd, &cfg->im_data[i * cfg->resolution.x + j], 4);
			j++;
		}
		i--;
	}
	return (SUCCESS);
}

static int	bitmap_info_header(t_config *cfg, int fd)
{
	int		header_info_size;
	int		plane_nbr;
	int		o_count;

	header_info_size = INFO_HEADER_SIZE;
	plane_nbr = 1;
	write(fd, &header_info_size, 4);
	write(fd, &cfg->resolution.x, 4);
	write(fd, &cfg->resolution.y, 4);
	write(fd, &plane_nbr, 2);
	write(fd, &cfg->mlx.pixel_bits, 2);
	o_count = -1;
	while (++o_count < 28)
		write(fd, "\0", 1);
	return (SUCCESS);
}

int			create_bitmap(t_config *cfg)
{
	int		fd;
	int		file_size;
	int		first_pix;
	char	*name;

	name = ft_strdup("image.bmp");
	fd = open(name, O_CREAT | O_RDWR, 0777);
	file_size = FILE_HEADER_SIZE + INFO_HEADER_SIZE + 4 + \
	(cfg->resolution.x * cfg->resolution.y * 4);
	first_pix = FILE_HEADER_SIZE + INFO_HEADER_SIZE + 4;
	write(fd, "BM", 2);
	write(fd, &file_size, 4);
	write(fd, "\0\0\0\0", 4);
	write(fd, &first_pix, 4);
	bitmap_info_header(cfg, fd);
	data_to_bitmap(cfg, fd);
	close(fd);
	free(name);
	return (SUCCESS);
}
