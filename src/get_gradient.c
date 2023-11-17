/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_gradient.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:31:00 by tspoof            #+#    #+#             */
/*   Updated: 2023/11/17 14:34:11 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_distance(int x0, int y0, int x1, int y1)
{
	return (sqrt(pow(y1 - y0, 2) + pow(x1 - x0, 2)));
}

static int	get_distance_delta(int delta_x, int delta_y)
{
	return (sqrt(pow(delta_y, 2) + pow(delta_x, 2)));
}

static float	ft_lerp(float a, float b, float fraction)
{
	return (a * (1.0 - fraction) + (b * fraction));
}

int	get_gradient(t_bres bres, int start_color, int end_color)
{
	float	tot_dist;
	float	cur_dist;
	int		r;
	int		g;
	int		b;

	tot_dist = get_distance_delta(bres.delta_x, abs(bres.delta_y));
	cur_dist = get_distance(bres.x0, bres.y0, bres.x1, bres.y1);
	r = ft_lerp(get_r(start_color), get_r(end_color), 1 - cur_dist / tot_dist);
	g = ft_lerp(get_g(start_color), get_g(end_color), 1 - cur_dist / tot_dist);
	b = ft_lerp(get_b(start_color), get_b(end_color), 1 - cur_dist / tot_dist);
	return (get_rgba(r, g, b, 0xFF));
}
