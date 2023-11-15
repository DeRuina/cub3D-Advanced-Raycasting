/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 10:02:10 by druina            #+#    #+#             */
/*   Updated: 2023/11/15 13:06:15 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_map(t_map *map)
{
	t_vec *m;

	map->max_height = -1;
	map->max_width = -1;
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

static t_player *init_player()
{

}

static void hehe_errror(mlx_t *mlx)
{
	mlx_close_window(mlx);
	ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
	dt_error(MLX_ERROR);
}

static t_cub init_cube(t_map *map)
{
	t_cub cub;

	cub.map = map;
	init_map(map);
	cub.mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!cub.mlx)
	{
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
		dt_error(MLX_ERROR);
	}
	cub.image = mlx_new_image(cub.mlx, 512, 512);
	if (!cub.image)
		hehe_errror(cub.mlx);
	if (mlx_image_to_window(cub.mlx, cub.image, 0, 0) == -1)
		hehe_errror(cub.mlx);
	cub.player = init_player();
	return (cub);
}





void print_map(t_map *map)
{
	char **map_rows;

	map_rows = (char **)map->map->memory;
	for (size_t i = 0; i < map->map->len; i++)
		printf("%s", map_rows[i]);


}

int	main(int argc, char **argv)
{
	t_map	map;
	t_cub	cub;

	if (argc != 2)
		dt_error(WRONG_AMOUNT);
	if (ft_strlen(ft_strnstr(argv[1], ".cub", ft_strlen(argv[1]))) != 4 && ft_strlen(argv[1]) > 4)
		dt_error(FILE_TYPE);
	cub = init_cube(&map);
	parse_map(argv[1], &map);
	print_map(&map);
	mlx_loop_hook(cub.mlx, draw, &cub);
	mlx_loop(cub.mlx);
	mlx_terminate(cub.mlx);
	destroy_map(&map);
	// system("leaks cub3D");
	return (0);
}

