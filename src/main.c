/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 10:02:10 by druina            #+#    #+#             */
/*   Updated: 2023/11/17 16:59:53 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void print_map(t_map *map)
{
	char **map_rows;

	map_rows = (char **)map->map->memory;
	for (size_t i = 0; i < map->map->len; i++)
		printf("%s", map_rows[i]);
}

// #include <stdio.h>
int	main(int argc, char **argv)
{
	t_cub	cub;

	if (argc != 2)
		dt_error(WRONG_AMOUNT);
	if (ft_strlen(ft_strnstr(argv[1], ".cub", ft_strlen(argv[1]))) != 4 && ft_strlen(argv[1]) > 4)
		dt_error(FILE_TYPE);
	cub = cub_init();
	parse_map(argv[1], &cub);
	// printf("angle: %.3f\n", cub.player->angle);
	// print_map(cub.map); // for debuging
	mlx_loop_hook(cub.mlx, draw, &cub);
	mlx_loop(cub.mlx);
	cub_destroy(&cub);
	system("leaks cub3D");
	return (0);
}

