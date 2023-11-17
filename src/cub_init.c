/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:54:59 by tspoof            #+#    #+#             */
/*   Updated: 2023/11/17 16:59:36 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void hehe_errror(mlx_t *mlx)
{
	mlx_close_window(mlx);
	ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
	dt_error(MLX_ERROR);
}

static t_map *init_map()
{
	t_map *map;
	t_vec *map_vec;

	map = malloc(sizeof(t_map));
	if (!map)
		dt_error(MALLOC_FAIL);
	map->max_height = -1;
	map->max_width = -1;
	map->cealing_color = -1;
	map->floor_color = -1;
	map->textures.ea = NULL;
	map->textures.no = NULL;
	map->textures.so = NULL;
	map->textures.we = NULL;
	map_vec = malloc(sizeof(t_vec));
	if (!map_vec)
		dt_error(MALLOC_FAIL);
	if (vec_new(map_vec, 10, sizeof(char *)) < 0)
		dt_error(MALLOC_FAIL);
	map->map = map_vec;
	return (map);
}

static t_player *init_player()
{
	t_player *player;

	player = malloc(sizeof(player));
	if (!player)
		dt_error(MALLOC_FAIL);
	ft_bzero(player, sizeof(t_player));
	return (player);
}

t_cub cub_init()
{
	t_cub cub;

	cub.map = init_map();
	cub.mlx = mlx_init(WIDTH, HEIGHT, "MLX42", true);
	if (!cub.mlx)
	{
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
		dt_error(MLX_ERROR);
	}
	cub.image = mlx_new_image(cub.mlx, WIDTH, HEIGHT);
	if (!cub.image)
		hehe_errror(cub.mlx);
	if (mlx_image_to_window(cub.mlx, cub.image, 0, 0) == -1)
		hehe_errror(cub.mlx);
	cub.player = init_player();
	return (cub);
}
