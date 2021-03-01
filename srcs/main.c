/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adel-sol <adel-sol@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/21 09:06:53 by adel-sol          #+#    #+#             */
/*   Updated: 2021/02/26 15:11:22 by adel-sol         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		start_game(t_config *cfg, int argc, char *argv[])
{
	cfg->mlx.line_bytes /= 4;
	build_lines(cfg);
	print_frame(cfg);
	if (argc == 3 && ft_strncmp(argv[2], "--save", 6) != 0)
		return (print_error("Unknown argument paseed!\n"));
	else if (argc == 3)
	{
		create_bitmap(cfg);
		ft_close(cfg, 10);
	}
	return (SUCCESS);
}

int		main(int argc, char *argv[])
{
	t_config	*cfg;

	if (argc > 3 || argc < 2)
		return (print_error("Invalid number of arguments!\n"));
	if (!(cfg = malloc(sizeof(t_config))))
		return (ft_close(cfg, 0));
	cos_sin_load(cfg);
	cfg->mlx.ptr = mlx_init();
	if (parse_all_params(argv[1], cfg) == ERROR)
		return (ft_close(cfg, 3));
	init_main_img(cfg);
	cfg->mlx.win = mlx_new_window(cfg->mlx.ptr, cfg->resolution.x, \
	cfg->resolution.y, "Cub3D");
	if (start_game(cfg, argc, argv) == ERROR)
		return (ERROR);
	mlx_hook(cfg->mlx.win, 2, 1L << 0, key_press, cfg);
	mlx_hook(cfg->mlx.win, 3, 1L << 1, key_release, cfg);
	mlx_hook(cfg->mlx.win, 17, 1L << 17, ft_close, cfg);
	mlx_loop_hook(cfg->mlx.ptr, do_action, cfg);
	mlx_loop(cfg->mlx.ptr);
	return (SUCCESS);
}
