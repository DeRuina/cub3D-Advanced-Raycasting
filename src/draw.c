/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:52:28 by tspoof            #+#    #+#             */
/*   Updated: 2023/11/17 14:28:45 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void draw_player(mlx_image_t *img, int x, int y, int width)
{
	int x_end;
	int y_end;
	int x_start;

	x_start = x;
	x_end = x + width;
	y_end = y + width;
	while (y < y_end)
	{
		x = x_start;
		while (x < x_end)
		{
			mlx_put_pixel(img, x, y, 0xFFFF00FF);
			x++;
		}
		y++;
	}
}

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
static void draw_rect(mlx_image_t *img, int x, int y, int width)
{
	int x_end;
	int y_end;
	int x_start;

	x_start = x;
	x_end = x + width;
	y_end = y + width;
	while (y < y_end)
	{
		x = x_start;
		while (x < x_end)
		{
			mlx_put_pixel(img, x, y, 0xFF0000FF);
			x++;
		}
		y++;
	}
}

int ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

void draw(void *param)
{
	t_cub *cub;
	int x;
	int y;
	int rect_len;
	char **map_rows;

	cub = param;
	rect_len = 16;
	draw_background(cub);
	map_rows = (char **)cub->map->map->memory;
	y = 0;
	while (y < cub->map->max_height)
	{
		x = 0;
		while (map_rows[y][x] && x < cub->map->max_width)
		{
			if (map_rows[y][x] == '1')
				draw_rect(cub->image, x * rect_len, y * rect_len, rect_len);
			if (is_player(map_rows[y][x]))
				draw_player(cub->image, x * rect_len, y * rect_len, rect_len); // rect_len / 2
			x++;
		}
		y++;
	}
	t_bres bres;

	bres.x0 = 64;
	bres.x1 = 512;
	bres.y0 = 64;
	bres.y1 = 512;
	plot_line(bres, cub->image, 0x00FF00FF, 0x0000FFFF);
}
