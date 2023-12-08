/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:52:28 by tspoof            #+#    #+#             */
/*   Updated: 2023/12/08 13:31:03 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_background(t_cub *cub)
{
	int	i;
	int	j;
	int	color;

	i = 0;
	color = cub->map->cealing_color;
	while (i < (int)cub->image->height)
	{
		j = 0;
		while (j < (int)cub->image->width)
		{
			if (i > (int)cub->image->width / 2)
				color = cub->map->floor_color;
			mlx_put_pixel(cub->image, j, i, color);
			j++;
		}
		i++;
	}
}

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

void	render(t_cub *cub)
{
	ft_memset(cub->image->pixels, 0, (cub->image->width * cub->image->height)
		* sizeof(int32_t));
	draw_background(cub);
	draw_walls(cub);
}
