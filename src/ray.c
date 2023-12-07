/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 12:59:39 by tspoof            #+#    #+#             */
/*   Updated: 2023/12/07 16:02:00 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// double posX = 22, posY = 12;      // x and y start position
// double dirX = 0, dirY = -1;       // initial direction vector
// double planeX = 0.66, planeY = 0; // the 2d raycaster version of camera plane

void cast_ray(int x, t_cub *cub)
{
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

}

static int	get_pixel(mlx_texture_t *texture, int x, int y)
{
	int	color;
	int	index;

	index = y * (int)texture->height
		* (int)texture->bytes_per_pixel + x
		* (int)texture->bytes_per_pixel;

	color = get_rgba(texture->pixels[index], texture->pixels[index + 1], texture->pixels[index + 2], 255);
	return (color);
}

int	get_texture_x(t_player *player, t_ray *ray)
{
	int text_x;
	double wall_x;

	if (ray->side == 0)
		wall_x = player->y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = player->x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	text_x = (int)(wall_x * (double)TEX_W);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		text_x = TEX_W - text_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		text_x = TEX_W - text_x - 1;

	return (text_x);
}

void	draw_pixels(int x, t_cub *cub, mlx_texture_t *texture)
{
	int		y;
	double	step;
	double	texture_pos;
	int text_x;
	int text_y;

	text_x = get_texture_x(cub->player, cub->ray);
	y = cub->ray->draw_start;
	step = 1.0 * ((double)TEX_H) / (double) cub->ray->line_height;
	texture_pos = ((double) cub->ray->draw_start - ((double)HEIGHT / 2.0)
			+ ((double) cub->ray->line_height / 2.0)) * step;
	while (y <  cub->ray->draw_end)
	{
		text_y = (int)texture_pos & (TEX_H - 1);
		texture_pos += step;
		mlx_put_pixel(cub->image, x, y, get_pixel(texture, text_x, text_y));
		y++;
	}
}

void	draw_wall(int x, t_cub *cub)
{
	t_ray *ray;
	t_player *player;

	ray = cub->ray;
	player = cub->player;
	if (ray->side == 0)
	{
		if (ray->map_x > player->x)
			draw_pixels(x, cub, cub->map->textures.ea);
		else
			draw_pixels(x, cub, cub->map->textures.we);
	}
	else if (ray->side == 1)
	{
		if (ray->map_y > player->y)
			draw_pixels(x, cub, cub->map->textures.so);
		else
			draw_pixels(x, cub, cub->map->textures.no);
	}
}
