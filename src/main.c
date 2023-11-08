/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 10:02:10 by druina            #+#    #+#             */
/*   Updated: 2023/11/08 13:18:02 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_map(t_map *map)
{
	t_vec *m;

	map->cealing_color = -1;
	map->floor_color = -1;
	map->textures.ea = NULL;
	map->textures.no = NULL;
	map->textures.so = NULL;
	map->textures.we = NULL;
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

int	main(int argc, char **argv)
{
	t_map	map;
	if (argc != 2)
		dt_error(WRONG_AMOUNT);
	if (ft_strlen(ft_strnstr(argv[1], ".cub", ft_strlen(argv[1]))) != 4 && ft_strlen(argv[1]) > 4)
		dt_error(FILE_TYPE);
	parse_map(argv[1], &map);
	init_map(&map);
	// mlx_t* mlx =mlx_init(100, 100, "Test", true);
	// if (!mlx)
	// 	error();
	// (void)mlx;
	destroy_map(&map);
	// system("leaks cub3D");
	return (0);
}

