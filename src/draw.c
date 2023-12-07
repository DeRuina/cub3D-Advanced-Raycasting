/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:52:28 by tspoof            #+#    #+#             */
/*   Updated: 2023/12/07 16:00:36 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


// for the minimap
// void draw_player(mlx_image_t *img, int x, int y, int width)
// {
// 	int x_end;
// 	int y_end;
// 	int x_start;

// 	x_start = x;
// 	x_end = x + width;
// 	y_end = y + width;
// 	while (y < y_end)
// 	{
// 		x = x_start;
// 		while (x < x_end)
// 		{
// 			mlx_put_pixel(img, x, y, 0xFFFF00FF);
// 			x++;
// 		}
// 		y++;
// 	}
// }

void draw_background(t_cub *cub)
{
	int i;
	int j;

	i = 0;
	while (i < (int)cub->image->height)
	{
		j = 0;
		while (j < (int)cub->image->width)
		{
			// do floor and ceiling
			mlx_put_pixel(cub->image, j, i, 0xFF);
			j++;
		}
		i++;
	}
}

// loop from the starting x to x + width
// loop from the starting y to y + width
// static void draw_rect(mlx_image_t *img, int x, int y, int width)
// {
// 	int x_end;
// 	int y_end;
// 	int x_start;

// 	x_start = x;
// 	x_end = x + width;
// 	y_end = y + width;
// 	while (y < y_end)
// 	{
// 		x = x_start;
// 		while (x < x_end)
// 		{
// 			mlx_put_pixel(img, x, y, 0xFF0000FF);
// 			x++;
// 		}
// 		y++;
// 	}
// }


// move to utils if needed
// int ft_max(int a, int b)
// {
// 	if (a > b)
// 		return (a);
// 	return (b);
// }


// int FixAng(int a) /// move this
// {
// 	if (a > 359)
// 	{
// 		a -= 360;
// 	}
// 	if (a < 0)
// 	{
// 		a += 360;
// 	}
// 	return a;
// }


// MINIMAP stuff
// int x;
// int y;
// int rect_len;
// char **map_rows;

// rect_len = 16;
// rect_len = 64;

// map_rows = (char **)cub->map->map->memory;
// y = 0;
// while (y < cub->map->max_height)
// {
// 	x = 0;
// 	while (map_rows[y][x] && x < cub->map->max_width)
// 	{
// 		if (map_rows[y][x] == '1')
// 			draw_rect(cub->image, x * rect_len, y * rect_len, rect_len);
// 		if (is_player(map_rows[y][x]))
// 			draw_player(cub->image, x * rect_len, y * rect_len, rect_len); // rect_len / 2
// 		x++;
// 	}
// 	y++;
// }

void	draw_walls(t_cub *cub)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		cast_ray(x, cub);
		draw_wall(x, cub);
		x++;
	}
}

void draw(t_cub *cub)
{
	// t_cub *cub;

	// cub = param;
	ft_memset(cub->image->pixels, 0, (cub->image->width * cub->image->height) * sizeof(int32_t));
	// // printf("%f\n", cub->ray->pos_x);
	// printf("%f\n", cub->ray->pos_y);
	// mlx_delete_image(cub->mlx, cub->image);
	// cub->image = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	// if (mlx_image_to_window(cub->mlx, cub->image, 0, 0) == -1)
	// 	exit(0); // hehe_error
	draw_background(cub);
	draw_walls(cub);
	cub->player->move_speed = cub->mlx->delta_time * 5.0;
}
