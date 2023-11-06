/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 10:02:10 by druina            #+#    #+#             */
/*   Updated: 2023/11/06 15:32:44 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_map(t_map *map)
{
	t_vec *m;

	map->cealing_color = -1;
	map->floor_color = -1;
	map->s_present.C = 0;
	map->s_present.EA = 0;
	map->s_present.F = 0;
	map->s_present.NO = 0;
	map->s_present.SO = 0;
	map->s_present.WE = 0;

	m = malloc(sizeof(t_vec));
	if (!m)
		dt_error(MALLOC_FAIL);
	if (vec_new(m, 10, sizeof(char *)) < 0)
		dt_error(MALLOC_FAIL);
	map->map = m;
}

static void	destroy_map(t_map *map)
{
	char **map_rows;
	size_t	i;

	// free map rows
	free(map->textures.ea);
	map->textures.ea = NULL;
	free(map->textures.so);
	map->textures.so = NULL;
	free(map->textures.we);
	map->textures.we = NULL;
	free(map->textures.no);
	map->textures.no = NULL;
	map_rows = (char **)map->map->memory;
	// free_2d(map_rows); //custom free for vector stuff
	i = 0;
	while (map->map->len && i < map->map->len)
	{
		free(map_rows[i]);
		map_rows[i] = NULL;
		i++;
	}
	vec_free(map->map);
	free(map->map);
}


// TODO:
// need to find a way to free the textures

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
	parse_map("./test/maps/good/cheese_maze.cub", &map);
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
	// system("leaks cub3D");
	return (0);
}

