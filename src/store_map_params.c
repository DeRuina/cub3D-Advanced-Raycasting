/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_map_params.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:55:56 by druina            #+#    #+#             */
/*   Updated: 2023/12/08 14:34:40 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	mlx_error(void)
{
	ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
	exit(EXIT_FAILURE);
}

static mlx_texture_t	*get_texture(char *line)
{
	char			*tmp;
	mlx_texture_t	*result;

	tmp = ft_strtrim(line, " \t\n");
	if (!tmp)
		dt_error(MALLOC_FAIL);
	result = mlx_load_png(tmp);
	free(tmp);
	if (!result)
		mlx_error();
	return (result);
}

static int	convert_color_value_to_int(char *value)
{
	int	result;

	value = ft_strtrim(value, " \t");
	if (!value)
		dt_error(MALLOC_FAIL);
	if (value[0] != '+' && !ft_isdigit(*value))
		dt_error(INVALID_COLOR);
	result = ft_atoi(value);
	if (result < 0 || result > 255)
		dt_error(INVALID_COLOR);
	free(value);
	return (result);
}

static int	get_color(char *line)
{
	char	**tmp;
	int		i;
	int		rgb[3];
	int		result;

	i = 0;
	tmp = ft_split(line, ',');
	if (!tmp)
		dt_error(MALLOC_FAIL);
	while (tmp[i])
	{
		if (i >= 3)
			dt_error(INVALID_COLOR);
		rgb[i] = convert_color_value_to_int(tmp[i]);
		i++;
	}
	if (i < 3)
		dt_error(INVALID_COLOR);
	result = get_rgba(rgb[0], rgb[1], rgb[2], 255);
	free_2d(tmp);
	return (result);
}

int	store_map_params(char **line, t_map *map)
{
	if (!ft_strncmp(*line, "SO ", 3) && !map->textures.so)
		map->textures.so = get_texture(*line + 2);
	else if (!ft_strncmp(*line, "NO ", 3) && !map->textures.no)
		map->textures.no = get_texture(*line + 2);
	else if (!ft_strncmp(*line, "WE ", 3) && !map->textures.we)
		map->textures.we = get_texture(*line + 2);
	else if (!ft_strncmp(*line, "EA ", 3) && !map->textures.ea)
		map->textures.ea = get_texture(*line + 2);
	else if (!ft_strncmp(*line, "F ", 2) && map->floor_color == -1)
		map->floor_color = get_color(*line + 1);
	else if (!ft_strncmp(*line, "C ", 2) && map->cealing_color == -1)
		map->cealing_color = get_color(*line + 1);
	else if (**line == '\n')
		return (CORRECT);
	else
		dt_error(INVALID_MAP);
	return (CORRECT);
}
