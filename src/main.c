/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 10:02:10 by druina            #+#    #+#             */
/*   Updated: 2023/10/31 17:23:14 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_map(t_map *map)
{
	t_vec *m;

	map->cealing_color = -1;
	map->floor_color = -1;

	m = malloc(sizeof(t_vec));
	if (!m)
		dt_error(MALLOC_FAIL);
	if (vec_new(m, 10, sizeof(char *)) < 0)
		dt_error(MALLOC_FAIL);
	map->map = m;
}

static void	destroy_map(t_map *map)
{
	// free map rows
	vec_free(map->map);
	free(map->map);
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
	parse_map("./test/maps/good/creepy.cub", &map);
	// int tmp = get_r(map.cealing_color);
	// tmp = get_g(map.cealing_color);
	// tmp = get_b(map.cealing_color);
	// // if (argc != 2)
	 	// dt_error(WRONG_AMOUNT);
	// if (ft_strlen(ft_strnstr(argv[1], ".cub", ft_strlen(argv[1]))) != 4 && ft_strlen(argv[1]) > 4)
	// dt_error(FILE_TYPE);
	// if (parse_map(argv[1], &map))
		// dt_error(INVALID_MAP);
	// argc = 0;
	// argv = NULL;
	destroy_map(&map);
	return (0);
}
