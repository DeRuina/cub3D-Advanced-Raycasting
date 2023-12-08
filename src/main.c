/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 10:02:10 by druina            #+#    #+#             */
/*   Updated: 2023/12/08 13:33:20 by druina           ###   ########.fr       */
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

void	rotate_left(t_player *player, mlx_t *mlx)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot_speed;

	rot_speed = mlx->delta_time * player->rot_speed;
	old_dir_x = player->dir_x;
	old_plane_x = player->plane_x;
	player->dir_x = player->dir_x * cos(-1.0 * rot_speed) - player->dir_y
		* sin(-1.0 * rot_speed);
	player->dir_y = old_dir_x * sin(-1.0 * rot_speed) + player->dir_y * cos(-1.0
			* rot_speed);
	player->plane_x = player->plane_x * cos(-1.0 * rot_speed) - player->plane_y
		* sin(-1.0 * rot_speed);
	player->plane_y = old_plane_x * sin(-1.0 * rot_speed) + player->plane_y
		* cos(-1.0 * rot_speed);
}

void	rotate_right(t_player *player, mlx_t *mlx)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot_speed;

	rot_speed = mlx->delta_time * player->rot_speed;
	old_dir_x = player->dir_x;
	old_plane_x = player->plane_x;
	player->dir_x = player->dir_x * cos(1.0 * rot_speed) - player->dir_y
		* sin(1.0 * rot_speed);
	player->dir_y = old_dir_x * sin(1.0 * rot_speed) + player->dir_y * cos(1.0
			* rot_speed);
	player->plane_x = player->plane_x * cos(1.0 * rot_speed) - player->plane_y
		* sin(1.0 * rot_speed);
	player->plane_y = old_plane_x * sin(1.0 * rot_speed) + player->plane_y
		* cos(1.0 * rot_speed);
}

void	my_keyhook(void *param)
{
	t_cub	*cub;

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
}

int	main(int argc, char **argv)
{
	t_cub	cub;

	if (argc != 2)
		dt_error(WRONG_AMOUNT);
	if (ft_strlen(ft_strnstr(argv[1], ".cub", ft_strlen(argv[1]))) != 4
		&& ft_strlen(argv[1]) > 4)
		dt_error(FILE_TYPE);
	cub = cub_init();
	parse_map(argv[1], &cub);
	mlx_loop_hook(cub.mlx, (void *)my_keyhook, &cub);
	mlx_loop_hook(cub.mlx, (void *)render, &cub);
	mlx_loop(cub.mlx);
	cub_destroy(&cub);
	return (0);
}
