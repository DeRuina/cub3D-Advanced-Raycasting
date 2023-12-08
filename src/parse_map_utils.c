/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 14:21:51 by druina            #+#    #+#             */
/*   Updated: 2023/12/08 14:28:56 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	valid_colors(t_map *map)
{
	if (map->cealing_color == -1 || map->floor_color == -1)
		return (0);
	return (1);
}

int	valid_textures(t_map *map)
{
	if (!map->textures.no || !map->textures.we || !map->textures.ea
		|| !map->textures.so)
		return (0);
	return (1);
}

int	is_edge(int j, int x_max, int i, int y_max)
{
	if (i <= 0 || i >= y_max)
		return (1);
	if (j <= 0 || j >= x_max)
		return (1);
	return (0);
}

void	count_player(int *player_count)
{
	(*player_count)++;
	if (*player_count > 1)
		dt_error(INVALID_MAP);
}
