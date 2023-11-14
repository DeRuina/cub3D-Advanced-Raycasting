/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:52:28 by tspoof            #+#    #+#             */
/*   Updated: 2023/11/14 14:36:59 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
			// do floor and ceiling
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
	int offset;
	char **map_rows;

	cub = param;
	offset = cub->image->width / ft_max(cub->map->max_height, cub->map->max_width);
	draw_background(cub);
	map_rows = (char **)cub->map->map->memory;
	y = 0;
	while (y < cub->map->max_height)
	{
		x = 0;
		while (map_rows[y][x] && x < cub->map->max_width)
		{
			if (map_rows[y][x] == '1')
				draw_rect(cub->image, x * offset, y * offset, offset);
			x++;
		}
		y++;
	}
}
