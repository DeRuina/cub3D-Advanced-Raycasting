/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 10:02:10 by druina            #+#    #+#             */
/*   Updated: 2023/11/09 13:53:59 by druina           ###   ########.fr       */
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
	cub.image = mlx_new_image(cub.mlx, 500, 500);
	if (!cub.image)
	{
		mlx_close_window(cub.mlx);
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
		dt_error(MLX_ERROR);
	}
	if (mlx_image_to_window(cub.mlx, cub.image, 0, 0) == -1)
	{
		mlx_close_window(cub.mlx);
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
		dt_error(MLX_ERROR);
	}
	return (cub);
}

void draw_map(void *param)
{
	t_cub *cub;
	int i;
	int j;

	cub = param;
	i = 0;
	while (i < (int)cub->image->height)
	{
		j = 0;
		while (j < (int)cub->image->width)
		{

			mlx_put_pixel(cub->image, j, i, 0xF1);
			j++;
		}
		i++;
	}


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
	mlx_loop_hook(cub.mlx, draw_map, &cub);
	mlx_loop(cub.mlx);
	mlx_terminate(cub.mlx);
	destroy_map(&map);
	// system("leaks cub3D");
	return (0);
}

