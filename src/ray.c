/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 12:59:39 by tspoof            #+#    #+#             */
/*   Updated: 2023/11/29 15:23:25 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// double posX = 22, posY = 12;      // x and y start position
// double dirX = 0, dirY = -1;       // initial direction vector
// double planeX = 0.66, planeY = 0; // the 2d raycaster version of camera plane

void ray(int x, t_cub *cub)
{
	t_bres	bres;
	t_ray	*r;
	t_player *player;
	t_map *map;
	mlx_image_t *image;


	r = cub->ray;
	player = cub->player;
	map = cub->map;
	image = cub->image;

	// double posX = cub->player->x / 64, posY = cub->player->y / 64;
	// int w = WIDTH; // ???
	// int h = HEIGHT;


		// calculate ray position and direction
		r->camera_x = 2 * x / (double)WIDTH - 1;
		// double cameraX = 2 * x / (double)WIDTH - 1; // x-coordinate in camera space
		r->ray_dir_x = player->dir_x + player->plane_x * r->camera_x;
		r->ray_dir_y = player->dir_y + player->plane_y * r->camera_x;
		// which box of the map we're in
		r->map_x = (int)player->x;
		r->map_y = (int)player->y;

		// length of ray from current position to next x or y-side
		// double sideDistX;
		// double sideDistY;

		// length of ray from one x or y-side to next x or y-side
		// these are derived as:
		// deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX))
		// deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY))
		// which can be simplified to abs(|rayDir| / rayDirX) and abs(|rayDir| / rayDirY)
		// where |rayDir| is the length of the vector (rayDirX, rayDirY). Its length,
		// unlike (dirX, dirY) is not 1, however this does not matter, only the
		// ratio between deltaDistX and deltaDistY matters, due to the way the DDA
		// stepping further below works. So the values can be computed as below.
		//  Division through zero is prevented, even though technically that's not
		//  needed in C++ with IEEE 754 floating point values.
		r->delta_dist_x = (r->ray_dir_x == 0) ? 1e30 : fabs(1 / r->ray_dir_x); // norminette
		r->delta_dist_y = (r->ray_dir_y == 0) ? 1e30 : fabs(1 / r->ray_dir_y);

		// double perpWallDist;

		// what direction to step in x or y-direction (either +1 or -1)
		// int stepX;
		// int stepY;

		r->hit = 0;
		// int hit = 0; // was there a wall hit?
		// int side;    // was a NS or a EW wall hit?
		// calculate step and initial sideDist
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
		// perform DDA
		while (r->hit == 0)
		{
			// jump to next map square, either in x-direction, or in y-direction
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
			// Check if ray has hit a wall
			if (((char **)map->map->memory)[r->map_y][r->map_x] == '1')
				r->hit = 1;
		}
		// Calculate distance projected on camera direction. This is the shortest distance from the point where the wall is
		// hit to the camera plane. Euclidean to center camera point would give fisheye effect!
		// This can be computed as (mapX - posX + (1 - stepX) / 2) / rayDirX for side == 0, or same formula with Y
		// for size == 1, but can be simplified to the code below thanks to how sideDist and deltaDist are computed:
		// because they were left scaled to |rayDir|. sideDist is the entire length of the ray above after the multiple
		// steps, but we subtract deltaDist once because one step more into the wall was taken above.
		if (r->side == 0)
			r->perp_wall_dist = (r->side_dist_x - r->delta_dist_x);
		else
			r->perp_wall_dist = (r->side_dist_y - r->delta_dist_y);

		// Calculate height of line to draw on screen
		r->line_height = (int)(HEIGHT / r->perp_wall_dist);

		// calculate lowest and highest pixel to fill in current stripe
		r->draw_start = -r->line_height / 2 + HEIGHT / 2;
		if (r->draw_start < 0)
			r->draw_start = 0;
		r->draw_end = r->line_height / 2 + HEIGHT / 2;
		if (r->draw_end >= HEIGHT)
			r->draw_end = HEIGHT - 1;

		int color = 0x00FF00FF;
		if (r->side == 1)
		{
			color = color / 2;
		}

		bres.x0 = x;
		bres.x1 = x;
		bres.y0 = r->draw_start;
		bres.y1 = r->draw_end;
		plot_line(bres, image, 0x00FF00FF, 0x0000FFFF);
}
