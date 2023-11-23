/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:53:21 by tspoof            #+#    #+#             */
/*   Updated: 2023/11/23 12:57:17 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	map->map = NULL;
	free(map);
	map = NULL;
}

static void destroy_player(t_player *player)
{
	free(player);
	player = NULL;
}

void cub_destroy(t_cub *cub)
{
	destroy_map(cub->map);
	destroy_player(cub->player);
	mlx_delete_image(cub->mlx, cub->image);
	mlx_terminate(cub->mlx);
	exit (0);
}
