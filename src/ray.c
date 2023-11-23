/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 12:42:02 by tspoof            #+#    #+#             */
/*   Updated: 2023/11/23 15:31:42 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define M_PI 3.14159265358979323846264338327950288

float degToRad(int a)
{
	return a * M_PI / 180.0;
}

// int FixAng(int a)
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

float distance(ax, ay, bx, by, ang)
{
	return cos(degToRad(ang)) * (bx - ax) - sin(degToRad(ang)) * (by - ay);
}

float *vertical_ray(float ray_angle, t_player *player, t_map *map)
{
	int depth_of_field;
	int side;
	float distance_vertical;
	float ray_x;
	float ray_y;
	float x_offset;
	float y_offset;

	float *result;

	// player->map_x = (int)player->x / 16; // change these to ray struct
	// player->map_y = (int)player->y / 16;

	//---Vertical---
	depth_of_field = 0;
	side = 0;
	distance_vertical = 100000;
	float Tan = tan(degToRad(ray_angle));
	if (cos(degToRad(ray_angle)) > 0.001)
	{
		ray_x = (((int)player->x >> 6) << 6) + 64;
		ray_y = (player->x - ray_x) * Tan + player->y;
		x_offset = 64;
		y_offset = -x_offset * Tan;
	} // looking left
	else if (cos(degToRad(ray_angle)) < -0.001)
	{
		ray_x = (((int)player->x >> 6) << 6) - 0.0001;
		ray_y = (player->x - ray_x) * Tan + player->y;
		x_offset = -64;
		y_offset = -x_offset * Tan;
	} // looking right
	else
	{
		ray_x = player->x;
		ray_y = player->y;
		depth_of_field = 8;
	} // looking up or down. no hit

	while (depth_of_field < 8)
		{
			player->map_x = (int)(ray_x) >> 6;
			player->map_y = (int)(ray_y) >> 6;

			// checks that ray hits the wall and is within the map
			if (player->map_y > 0
				&& player->map_y < map->max_height
				&& player->map_x < (int)ft_strlen(((char**)map->map->memory)[player->map_y])
				&& ((char**)map->map->memory)[player->map_y][player->map_x] == '1')
			{
				depth_of_field = 8;
				distance_vertical = cos(degToRad(ray_angle)) * (ray_x - player->x) - sin(degToRad(ray_angle)) * (ray_y - player->y);
			} // hit
			else
			{
				ray_x += x_offset;
				ray_y += y_offset;
				depth_of_field += 1;
			} // check next horizontal
		}
		result = malloc(sizeof(float) * 3);
		result[0] = ray_x;
		result[1] = ray_y;
		result[2] = distance_vertical;
		return (result);
}


// void horizontal_ray(float ray_angle, t_cub *cub)
// {
// 	int depth_of_field;
// 	float distance_horizontal;
// 	float Tan;
// 	float ray_x;
// 	float ray_y;

// 	float x_offset;
// 	float y_offset;

// 	// t_player
// 	float player->x;
// 	float player->y;


// 	//---Horizontal---
// 	depth_of_field = 0;
// 	distance_horizontal = 100000;
// 	Tan = 1.0 / Tan;
// 	if (sin(degToRad(ray_angle)) > 0.001)
// 	{
// 		ray_y = (((int)player->y >> 6) << 6) - 0.0001;
// 		ray_x = (player->y - ray_y) * Tan + player->x;
// 		y_offset = -64;
// 		x_offset = -y_offset * Tan;
// 	} // looking up
// 	else if (sin(degToRad(ray_angle)) < -0.001)
// 	{
// 		ray_y = (((int)player->y >> 6) << 6) + 64;
// 		ray_x = (player->y - ray_y) * Tan + player->x;
// 		y_offset = 64;
// 		x_offset = -y_offset * Tan;
// 	} // looking down
// 	else
// 	{
// 		ray_x = player->x;
// 		ray_y = player->y;
// 		depth_of_field = 8;
// 	} // looking straight left or right

// 	while (depth_of_field < 8)
// 	{
// 		player->map_x = (int)(ray_x) >> 6;
// 		player->map_y = (int)(ray_y) >> 6;
// 		map_position = player->map_y * mapX + player->map_x;
// 		if (map_position > 0 && map_position < mapX * mapY && map[map_position] == 1)
// 		{
// 			depth_of_field = 8;
// 			distance_horizontal = cos(degToRad(ray_angle)) * (ray_x - player->x) - sin(degToRad(ray_angle)) * (ray_y - player->y);
// 		} // hit
// 		else
// 		{
// 			ray_x += x_offset;
// 			ray_y += y_offset;
// 			depth_of_field += 1;
// 		} // check next horizontal
// 	}
// }
