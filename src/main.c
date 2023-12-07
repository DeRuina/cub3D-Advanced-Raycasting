/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 10:02:10 by druina            #+#    #+#             */
/*   Updated: 2023/12/07 17:29:53 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void move_up(t_player *player, t_map *map, mlx_t *mlx)
{
	int	x;
	int	y;
	char **m;
	double move_speed;

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
void move_left(t_player *player, t_map *map, mlx_t *mlx)
{
	int	x;
	int	y;
	char **m;
	double move_speed;

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
void move_down(t_player *player, t_map *map, mlx_t *mlx)
{
	int	x;
	int	y;
	char **m;
	double move_speed;

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
void move_right(t_player *player, t_map *map, mlx_t *mlx)
{
	int	x;
	int	y;
	char **m;
	double move_speed;

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


void rotate_left(t_player *player, mlx_t *mlx)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot_speed;

	rot_speed = mlx->delta_time * player->rot_speed;
	old_dir_x = player->dir_x;
	old_plane_x = player->plane_x;
	player->dir_x = player->dir_x * cos(-1.0 * rot_speed) - player->dir_y
		* sin(-1.0 * rot_speed);
	player->dir_y = old_dir_x * sin(-1.0 * rot_speed) + player->dir_y
		* cos(-1.0 * rot_speed);
	player->plane_x = player->plane_x * cos(-1.0 * rot_speed)
		- player->plane_y * sin(-1.0 * rot_speed);
	player->plane_y = old_plane_x * sin(-1.0 * rot_speed)
		+ player->plane_y * cos(-1.0 * rot_speed);
}

void rotate_right(t_player *player, mlx_t *mlx)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot_speed;

	rot_speed = mlx->delta_time * player->rot_speed;
	old_dir_x = player->dir_x;
	old_plane_x = player->plane_x;
	player->dir_x = player->dir_x * cos(1.0 * rot_speed) - player->dir_y
		* sin(1.0 * rot_speed);
	player->dir_y = old_dir_x * sin(1.0 * rot_speed) + player->dir_y
		* cos(1.0 * rot_speed);
	player->plane_x = player->plane_x * cos(1.0 * rot_speed)
		- player->plane_y * sin(1.0 * rot_speed);
	player->plane_y = old_plane_x * sin(1.0 * rot_speed) + player->plane_y
		* cos(1.0 * rot_speed);
}

// void my_keyhook(mlx_key_data_t keydata, void* param)
void my_keyhook(void* param)
{
	t_cub *cub;

	cub = param;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
		exit(0);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_W))
		move_up(cub->player, cub->map, cub->mlx);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_A))
		move_left(cub->player, cub->map, cub->mlx);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_S))
		move_down(cub->player, cub->map, cub->mlx);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_D))
		move_right(cub->player, cub->map, cub->mlx);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
		rotate_right(cub->player, cub->mlx);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
		rotate_left(cub->player, cub->mlx);
	// if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
	// {
    //   // both camera direction and camera plane must be rotated
    //   double oldDirX = dirX;
    //   dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
    //   dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
    //   double oldPlaneX = planeX;
    //   planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
    //   planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
    // }
	// if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
	// {
    //   if (worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false)
    //     posX -= dirX * moveSpeed;
    //   if (worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false)
    //     posY -= dirY * moveSpeed;
    // }
	// if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
	// {
    //   // both camera direction and camera plane must be rotated
    //   double oldDirX = dirX;
    //   dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
    //   dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
    //   double oldPlaneX = planeX;
    //   planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
    //   planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
    // }

}

void print_map(t_map *map)
{
	char **map_rows;

	map_rows = (char **)map->map->memory;
	for (size_t i = 0; i < map->map->len; i++)
		printf("%s", map_rows[i]);
}

// #include <stdio.h>
int	main(int argc, char **argv)
{
	t_cub	cub;

	if (argc != 2)
		dt_error(WRONG_AMOUNT);
	if (ft_strlen(ft_strnstr(argv[1], ".cub", ft_strlen(argv[1]))) != 4 && ft_strlen(argv[1]) > 4)
		dt_error(FILE_TYPE);
	cub = cub_init();
	parse_map(argv[1], &cub);
	// printf("angle: %.3f\n", cub->player->angle);
	// print_map(cub->map); // for debuging

	mlx_loop_hook(cub.mlx, (void *)my_keyhook, &cub);
	mlx_loop_hook(cub.mlx, (void *)render, &cub);
	mlx_loop(cub.mlx);
	cub_destroy(&cub);
	system("leaks cub3D");
	return (0);
}

