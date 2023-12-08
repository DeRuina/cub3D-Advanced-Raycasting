/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validity.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 14:28:21 by druina            #+#    #+#             */
/*   Updated: 2023/12/08 14:30:07 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_validity(t_map *map)
{
	if (!map->map->len || !valid_map(map))
		dt_error(INVALID_MAP);
	if (!valid_colors(map))
		dt_error(INVALID_COLOR);
	if (!valid_textures(map))
		dt_error(INVALID_TEXTURE);
}

int	check_row(char **rows, int i, int j, int len)
{
	if (rows[i][j] == '0' || is_player(rows[i][j]))
	{
		if (is_edge(j, ft_strlen(rows[i]), i, len))
			return (0);
		if (rows[i - 1][j] != '1' && rows[i - 1][j] != '0' && !is_player(rows[i
				- 1][j]))
			return (0);
		if (rows[i + 1][j] != '1' && rows[i + 1][j] != '0' && !is_player(rows[i
				+ 1][j]))
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

int	is_player(char c)
{
	int			i;
	static char	player[] = {'N', 'W', 'E', 'S', '\0'};

	i = 0;
	while (player[i])
	{
		if (player[i] == c)
			return (player[i]);
		i++;
	}
	return (0);
}

int	valid_map(t_map *map)
{
	size_t	i;
	size_t	j;
	char	**rows;
	int		player_count;

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
