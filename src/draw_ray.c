/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:16:12 by druina            #+#    #+#             */
/*   Updated: 2023/12/11 15:17:13 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_pixel(mlx_texture_t *texture, int x, int y)
{
	int	color;
	int	index;

	index = y * (int)texture->height * (int)texture->bytes_per_pixel + x
		* (int)texture->bytes_per_pixel;
	color = get_rgba(texture->pixels[index], texture->pixels[index + 1],
			texture->pixels[index + 2], 255);
	return (color);
}

int	get_texture_x(t_player *player, t_ray *ray)
{
	int		text_x;
	double	wall_x;

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
	int		text_x;
	int		text_y;

	text_x = get_texture_x(cub->player, cub->ray);
	y = cub->ray->draw_start;
	step = 1.0 * ((double)TEX_H) / (double)cub->ray->line_height;
	texture_pos = ((double)cub->ray->draw_start - ((double)HEIGHT / 2.0)
			+ ((double)cub->ray->line_height / 2.0)) * step;
	while (y < cub->ray->draw_end)
	{
		text_y = (int)texture_pos & (TEX_H - 1);
		texture_pos += step;
		mlx_put_pixel(cub->image, x, y, get_pixel(texture, text_x, text_y));
		y++;
	}
}

void	draw_wall(int x, t_cub *cub)
{
	t_ray		*ray;
	t_player	*player;

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
