/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 10:02:10 by druina            #+#    #+#             */
/*   Updated: 2023/11/07 14:01:16 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	destroy_map(t_map *map)
{
	char **map_rows;
	size_t	i;

	if (map->s_present.EA)
		mlx_delete_texture(map->textures.ea);
	if (map->s_present.SO)
		mlx_delete_texture(map->textures.so);
	if (map->s_present.WE)
		mlx_delete_texture(map->textures.we);
	if (map->s_present.NO)
		mlx_delete_texture(map->textures.no);
	map_rows = (char **)map->map->memory;
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

static void	destroy_map(t_map *map)
{
	char **map_rows;
	size_t	i;

	if (map->textures.ea)
		mlx_delete_texture(map->textures.ea);
	if (map->textures.so)
		mlx_delete_texture(map->textures.so);
	if (map->textures.we)
		mlx_delete_texture(map->textures.we);
	if (map->textures.no)
		mlx_delete_texture(map->textures.no);
	map_rows = (char **)map->map->memory;
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

