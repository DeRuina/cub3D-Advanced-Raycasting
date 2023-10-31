/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:55:42 by druina            #+#    #+#             */
/*   Updated: 2023/10/31 16:55:58 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

static int	valid_map_chars(char *line)
{
	while (line && *line)
	{
		if (*line != ' '
			&& *line != '0'
			&& *line != '1'
			&& *line != 'S'
			&& *line != 'N'
			&& *line != 'E'
			&& *line != 'W'
			&& *line != '\n')
			return (0);
		line++;
	}
	return (1);
}

void	store_map(char *line, t_map *map)
{
	char *tmp;

	if (!valid_map_chars(line))
		dt_error(INVALID_MAP);
	tmp = ft_strtrim(line, " \t");
	if (tmp && tmp[0] == '\n')
	{
		// if (map->map->len != 0) // breaks the thing if there is a /n at the end
		// 	dt_error(INVALID_MAP);
		return;
	}
	free(tmp);
	if (vec_push(map->map, &line) < 0)
		dt_error(MALLOC_FAIL);
	size_t i = 0;
	char **str = (char **)map->map->memory;
	while (i < map->map->len)
	{
		printf("%s\n", str[i]);
		i++;
	}
}
