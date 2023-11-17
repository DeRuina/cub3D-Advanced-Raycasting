/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 14:31:07 by tspoof            #+#    #+#             */
/*   Updated: 2023/11/17 16:06:21 by tspoof           ###   ########.fr       */
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
			return (player[i]);
		i++;
	}
	return (0);
}
static int check_row(char **rows, int i, int j, int len)
{
	if (rows[i][j] == '0' || is_player(rows[i][j]))
	{
		if (is_edge(j, ft_strlen(rows[i]), i, len))
			return (0);
		if (rows[i - 1][j] != '1' && rows[i - 1][j] != '0'
			&& !is_player(rows[i - 1][j]))
			return (0);
		if (rows[i + 1][j] != '1' && rows[i + 1][j] != '0'
			&& !is_player(rows[i + 1][j]))
			return (0);
		if (rows[i][j + 1] != '1' && rows[i][j + 1] != '0'
			&& !is_player(rows[i][j + 1]))
			return (0);
		if (rows[i][j - 1] != '1' && rows[i][j - 1] != '0'
			&& !is_player(rows[i][j - 1]))
			return (0);
	}
	return (1);
}

static void count_player(int *player_count)
{
	(*player_count)++;
	if (*player_count > 1)
		dt_error(INVALID_MAP);
}

int valid_map(t_map *map)
{
	size_t i;
	size_t j;
	char **rows;
	int player_count;

	player_count = 0;
	i = 0;
	rows = (char **)map->map->memory;
	while (map->map->len != 0 && i < map->map->len)
	{
		j = 0;
		while (rows[i] && rows[i][j])
		{
			if (is_player(rows[i][j]))
				count_player(&player_count);
			if (!check_row(rows, i, j, map->map->len))
				dt_error(INVALID_MAP);
			j++;
		}
		i++;
	}
	if (!player_count)
		dt_error(NO_PLAYER);
	return (1);
}


static void get_params(int fd, t_map *map)
{
	char	*line;
	char	*tmp;

	line = NULL;
	while ((line = get_next_line(fd)))
	{
		tmp = ft_strtrim(line, " \t");
		if (!tmp)
			dt_error(MALLOC_FAIL);
		free(line);
		line = tmp;
		(void)store_map_params(&line, map);
		free(line);
		line = NULL;
		if (valid_colors(map) && valid_textures(map))
			return;
	}
}

static void get_map(int fd, t_map *map)
{
	char	*line;

	line = NULL;
	while ((line = get_next_line(fd)))
	{
		store_map(line, map);
		free(line);
		line = NULL;
	}
}

static void check_validity(t_map *map)
{
	if (!map->map->len || !valid_map(map))
		dt_error(INVALID_MAP);
	if (!valid_colors(map))
		dt_error(INVALID_COLOR);
	if (!valid_textures(map))
		dt_error(INVALID_TEXTURE);
}

static void get_max_dimensions(t_map *map)
{
	size_t	y;
	int	row_len;

	row_len = 0;
	y = 0;
	map->max_height = map->map->len;
	while (y < map->map->len)
	{
		row_len = ft_strlen(((char **)map->map->memory)[y]) - 1; // -1 for newline
		if (row_len > map->max_width)
			map->max_width = row_len;
		y++;
	}
}

static float get_player_angle(char c)
{
	if ((char)(is_player(c)) == 'N')
		return (0.0f);
	else if ((char)(is_player(c)) == 'E')
		return (90.0f);
	else if ((char)(is_player(c)) == 'S')
		return (180.0f);
	else if ((char)(is_player(c)) == 'W')
		return (270.0f);
	return (0.0f);
}

static void get_player(t_map *map, t_player *player)
{
	char **rows;
	size_t i;
	size_t j;
	(void)player;

	rows = (char **)map->map->memory;

	i = 0;
	while (map->map->len != 0 && i < map->map->len)
	{
		j = 0;
		while (rows[i] && rows[i][j])
		{
			if (is_player(rows[i][j]))
			{
				player->x = (float)j;
				player->y = (float)i;
				// player->map_x = j;
				// player->map_y = i;

				player->angle = get_player_angle(rows[i][j]);
				return ;
			}
			j++;
		}
		i++;
	}
}

int	parse_map(char *path, t_cub *cub)
{
	int		fd;
	t_map *map;
	t_player *player;

	map = cub->map;
	player = cub->player;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		dt_error(FILE_OPEN);
	get_params(fd, map);
	get_map(fd, map);
	check_validity(map);
	get_max_dimensions(map);
	get_player(map, player);
	close(fd);
	return (0);
}
