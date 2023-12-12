/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 14:31:07 by tspoof            #+#    #+#             */
/*   Updated: 2023/12/12 10:54:56 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_player(t_map *map, t_player *player)
{
	char	**rows;
	size_t	i;
	size_t	j;

	rows = (char **)map->map->memory;
	i = 0;
	while (map->map->len != 0 && i < map->map->len)
	{
		j = 0;
		while (rows[i] && rows[i][j])
		{
			if (is_player(rows[i][j]))
			{
				player->x = (double)j + 0.2;
				player->y = (double)i + 0.2;
				set_player_angle(rows[i][j], player);
				return ;
			}
			j++;
		}
		i++;
	}
}

static void	get_max_dimensions(t_map *map)
{
	size_t	y;
	int		row_len;

	row_len = 0;
	y = 0;
	map->max_height = map->map->len;
	while (y < map->map->len)
	{
		row_len = ft_strlen(((char **)map->map->memory)[y]) - 1;
		if (row_len > map->max_width)
			map->max_width = row_len;
		y++;
	}
}

static void	get_map(int fd, t_map *map)
{
	char	*line;

	line = NULL;
	if (handle_empty_lines(fd, &line) == 2)
		dt_error(INVALID_MAP);
	while (1)
	{
		if (store_map(line, map))
			break ;
		free(line);
		line = NULL;
		line = get_next_line(fd);
		if (line == NULL)
			return ;
	}
	if (handle_empty_lines(fd, &line) == 1)
		dt_error(INVALID_MAP);
}

static void	get_params(int fd, t_map *map)
{
	char	*line;
	char	*tmp;

	line = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			return ;
		tmp = ft_strtrim(line, " \t");
		if (!tmp)
			dt_error(MALLOC_FAIL);
		free(line);
		line = tmp;
		(void)store_map_params(&line, map);
		free(line);
		line = NULL;
		if (valid_colors(map) && valid_textures(map))
			return ;
	}
}

int	parse_map(char *path, t_cub *cub)
{
	int			fd;
	t_map		*map;
	t_player	*player;

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
