/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 12:59:39 by tspoof            #+#    #+#             */
/*   Updated: 2023/12/11 16:38:52 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ray(t_ray *r)
{
	if (r->side == 0)
		r->perp_wall_dist = (r->side_dist_x - r->delta_dist_x);
	else
		r->perp_wall_dist = (r->side_dist_y - r->delta_dist_y);
	r->line_height = (int)(HEIGHT / r->perp_wall_dist);
	r->draw_start = -r->line_height / 2 + HEIGHT / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = r->line_height / 2 + HEIGHT / 2;
	if (r->draw_end >= HEIGHT)
		r->draw_end = HEIGHT - 1;
}

static void	perform_dda(t_ray *r, t_map *map)
{
	char	**map_memory;

	map_memory = (char **)map->map->memory;
	r->hit = 0;
	while (r->hit == 0)
	{
		if (r->side_dist_x < r->side_dist_y)
		{
			r->side_dist_x += r->delta_dist_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_dist_y += r->delta_dist_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if (r->map_y < 0 || r->map_y >= map->max_height || r->map_x < 0
			|| r->map_x >= (int)ft_strlen(map_memory[r->map_y]))
			break ;
		if (((char **)map->map->memory)[r->map_y][r->map_x] == '1')
			r->hit = 1;
	}
}

static void	step_and_side_dist(t_ray *r, t_player *player)
{
	if (r->ray_dir_x < 0)
	{
		r->step_x = -1;
		r->side_dist_x = (player->x - r->map_x) * r->delta_dist_x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = (r->map_x + 1.0 - player->x) * r->delta_dist_x;
	}
	if (r->ray_dir_y < 0)
	{
		r->step_y = -1;
		r->side_dist_y = (player->y - r->map_y) * r->delta_dist_y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y = (r->map_y + 1.0 - player->y) * r->delta_dist_y;
	}
}

static void	delta_distance(t_ray *r, t_player *player, int x)
{
	r->camera_x = 2 * x / (double)WIDTH - 1;
	r->ray_dir_x = player->dir_x + player->plane_x * r->camera_x;
	r->ray_dir_y = player->dir_y + player->plane_y * r->camera_x;
	r->map_x = (int)player->x;
	r->map_y = (int)player->y;
	if (r->ray_dir_x == 0)
		r->delta_dist_x = 1e30;
	else
		r->delta_dist_x = fabs(1 / r->ray_dir_x);
	if (r->ray_dir_y == 0)
		r->delta_dist_y = 1e30;
	else
		r->delta_dist_y = fabs(1 / r->ray_dir_y);
}

void	cast_ray(int x, t_cub *cub)
{
	t_ray		*r;
	t_player	*player;
	t_map		*map;
	mlx_image_t	*image;

	r = cub->ray;
	player = cub->player;
	map = cub->map;
	image = cub->image;
	delta_distance(r, player, x);
	step_and_side_dist(r, player);
	perform_dda(r, map);
	ray(r);
}
