/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:55:42 by druina            #+#    #+#             */
/*   Updated: 2023/12/08 13:49:42 by druina           ###   ########.fr       */
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

int	is_only_nl(char *str)
{
	char	*tmp;

	tmp = ft_strtrim(str, " \t");
	if (!tmp)
		dt_error(MALLOC_FAIL);
	if (tmp && tmp[0] == '\n')
	{
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}

void	store_map(char *line, t_map *map)
{
	char	*tmp;

	if (!valid_map_chars(line))
		dt_error(INVALID_MAP);
	if (is_only_nl(line))
		return ;
	tmp = ft_strdup(line);
	if (!tmp)
		dt_error(MALLOC_FAIL);
	if (vec_push(map->map, &tmp) < 0)
		dt_error(MALLOC_FAIL);
}
