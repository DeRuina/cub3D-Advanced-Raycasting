/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 13:53:34 by druina            #+#    #+#             */
/*   Updated: 2023/12/08 13:54:05 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_up(t_player *player, t_map *map, mlx_t *mlx)
{
	int		x;
	int		y;
	char	**m;
	double	move_speed;

	move_speed = mlx->delta_time * player->move_speed;
	m = (char **)(map->map->memory);
	x = (int)(player->x + player->dir_x * move_speed);
	y = (int)player->y;
	if (m[y][x] != '1')
		player->x += player->dir_x * move_speed;
	x = (int)(player->x);
	y = (int)(player->y + player->dir_y * move_speed);
	if (m[y][x] != '1')
		player->y += player->dir_y * move_speed;
}

void	move_left(t_player *player, t_map *map, mlx_t *mlx)
{
	int		x;
	int		y;
	char	**m;
	double	move_speed;

	move_speed = mlx->delta_time * player->move_speed;
	m = (char **)(map->map->memory);
	x = (int)(player->x + player->dir_y * move_speed);
	y = (int)player->y;
	if (m[y][x] != '1')
		player->x += player->dir_y * move_speed;
	x = (int)(player->x);
	y = (int)(player->y + player->dir_x * move_speed);
	if (m[y][x] != '1')
		player->y -= player->dir_x * move_speed;
}

void	move_down(t_player *player, t_map *map, mlx_t *mlx)
{
	int		x;
	int		y;
	char	**m;
	double	move_speed;

	move_speed = mlx->delta_time * player->move_speed;
	m = (char **)(map->map->memory);
	x = (int)(player->x - player->dir_x * move_speed);
	y = (int)player->y;
	if (m[y][x] != '1')
		player->x -= player->dir_x * move_speed;
	x = (int)(player->x);
	y = (int)(player->y - player->dir_y * move_speed);
	if (m[y][x] != '1')
		player->y -= player->dir_y * move_speed;
}

void	move_right(t_player *player, t_map *map, mlx_t *mlx)
{
	int		x;
	int		y;
	char	**m;
	double	move_speed;

	move_speed = mlx->delta_time * player->move_speed;
	m = (char **)(map->map->memory);
	x = (int)(player->x - player->dir_y * move_speed);
	y = (int)player->y;
	if (m[y][x] != '1')
		player->x -= player->dir_y * move_speed;
	x = (int)(player->x);
	y = (int)(player->y + player->dir_x * move_speed);
	if (m[y][x] != '1')
		player->y += player->dir_x * move_speed;
}
