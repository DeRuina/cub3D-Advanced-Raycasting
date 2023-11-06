/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 14:31:07 by tspoof            #+#    #+#             */
/*   Updated: 2023/11/06 15:17:28 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int valid_colors(t_map *map)
{
	if (map->cealing_color == -1 || map->floor_color == -1)
		return (0);
	return (1);
}

int valid_textures(t_map *map)
{
	if (!map->textures.no || !map->textures.we || !map->textures.ea
		 || !map->textures.so)
		 	return (0);
	return (1);
}


int is_edge(int j, int x_max, int i, int y_max)
{
	if (i <= 0 || i >= y_max)
		return (1);
	if (j <= 0 || j >= x_max)
		return (1);
	return (0);
}

int is_player(char c)
{
	static char player[] = {'N', 'W', 'E', 'S', '\0'};
	int	i;

	i = 0;
	while(player[i])
	{
		if (player[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int check_map(t_map *map)
{
	int player_count;
	size_t i;
	size_t j;
	char **rows;

	player_count = 0;
	i = 0;
	rows = (char **)map->map->memory;
	while (map->map->len != 0 && i < map->map->len)
	{
		j = 0;
		while (rows[i] && rows[i][j])
		{
			if (is_player(rows[i][j]))
			{
				player_count++;
				if (player_count > 1)
					dt_error(INVALID_MAP);
			}
			if (rows[i][j] == '0' || is_player(rows[i][j]))
			{
				if (is_edge(j, ft_strlen(rows[i]), i, map->map->len))
					dt_error(INVALID_MAP);
				if (rows[i - 1][j] != '1' && rows[i - 1][j] != '0' && !is_player(rows[i - 1][j]))
					dt_error(INVALID_MAP);
				if (rows[i + 1][j] != '1' && rows[i + 1][j] != '0' && !is_player(rows[i + 1][j]))
					dt_error(INVALID_MAP);
				if (rows[i][j + 1] != '1' && rows[i][j + 1] != '0' && !is_player(rows[i][j + 1]))
					dt_error(INVALID_MAP);
				if (rows[i][j - 1] != '1' && rows[i][j - 1] != '0'&& !is_player(rows[i][j - 1]))
					dt_error(INVALID_MAP);
			}

			j++;
		}
		i++;
	}
	if (!player_count)
		dt_error(NO_PLAYER);
	return (0);
}

// what happens if we have duplicates
int	parse_map(char *path, t_map *map)
{
	int		fd;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		dt_error(FILE_OPEN);
	line = NULL;
	while ((line = get_next_line(fd)))
	{
		(void)store_map_params(&line, map);
		free(line);
		line = NULL;
		if (valid_colors(map) && valid_textures(map))
			break;
	}
	while ((line = get_next_line(fd)))
	{
		store_map(line, map);
		free(line);
		line = NULL;
	}
	(void)check_map(map);
	if (!valid_colors(map) || !valid_textures(map) || !map->map->len)
		dt_error(INVALID_MAP);
	close(fd);
	return (0);
}
