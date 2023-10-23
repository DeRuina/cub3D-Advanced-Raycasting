/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 10:02:10 by druina            #+#    #+#             */
/*   Updated: 2023/10/23 12:52:22 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_map(t_map *map)
{
	map->cealing_color = -1;
	map->floor_color = -1;
}

int	main(int argc, char **argv)
{
	t_map	map;

	(void)argc;
	(void)argv;

	init_map(&map);
	// mlx_t* mlx =mlx_init(100, 100, "Test", true);
	// if (!mlx)
	// 	error();
// (void)mlx;
	parse_map("./test/maps/bad/color_missing.cub", &map);
	int tmp = get_r(map.cealing_color);
	tmp = get_g(map.cealing_color);
	tmp = get_b(map.cealing_color);
	// if (argc != 2)
	 	// dt_error(WRONG_AMOUNT);
	// if (ft_strlen(ft_strnstr(argv[1], ".cub", ft_strlen(argv[1]))) != 4 && ft_strlen(argv[1]) > 4)
	// dt_error(FILE_TYPE);
	// if (parse_map(argv[1], &map))
		// dt_error(INVALID_MAP);
	// argc = 0;
	// argv = NULL;
	return (0);
}
