/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:54:59 by tspoof            #+#    #+#             */
/*   Updated: 2023/12/07 17:21:16 by tspoof           ###   ########.fr       */
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

	player = malloc(sizeof(t_player));
	if (!player)
		dt_error(MALLOC_FAIL);
	ft_bzero(player, sizeof(t_player));
	player->move_speed = 4.0;
	player->rot_speed = 3.0;
	return (player);
}

static t_ray *init_ray()
{
	t_ray *ray;

	ray = malloc(sizeof(t_ray));
	if (!ray)
		dt_error(MALLOC_FAIL);
	ft_bzero(ray, sizeof(t_ray));
	return (ray);
}

t_cub cub_init()
{
	t_cub cub;

	cub.map = init_map();
	cub.mlx = mlx_init(WIDTH, HEIGHT, "MLX42", false);
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
	cub.ray = init_ray();
	return (cub);
}
