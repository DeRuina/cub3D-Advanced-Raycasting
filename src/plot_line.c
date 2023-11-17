/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:08:09 by tspoof            #+#    #+#             */
/*   Updated: 2023/11/17 14:32:15 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_sign(int a, int b)
{
	if (a < b)
		return (1);
	else
		return (-1);
}

void	plot_line(t_bres bres, mlx_image_t *img, int start_color, int end_color)
{
	int	e2;

	bres.delta_x = abs(bres.x1 - bres.x0);
	bres.delta_y = -abs(bres.y1 - bres.y0);
	bres.sign_x = get_sign(bres.x0, bres.x1);
	bres.sign_y = get_sign(bres.y0, bres.y1);
	bres.err = bres.delta_x + bres.delta_y;
	while (1)
	{
		mlx_put_pixel(img, bres.x0, bres.y0,
			get_gradient(bres, start_color, end_color));
		if (bres.x0 == bres.x1 && bres.y0 == bres.y1)
			break ;
		e2 = 2 * bres.err;
		if (e2 >= bres.delta_y && bres.x0 != bres.x1)
		{
			bres.err += bres.delta_y;
			bres.x0 += bres.sign_x;
		}
		if (e2 <= bres.delta_x && bres.y0 != bres.y1)
		{
			bres.err += bres.delta_x;
			bres.y0 += bres.sign_y;
		}
	}
}
