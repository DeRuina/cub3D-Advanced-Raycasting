/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_map_params.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:55:56 by druina            #+#    #+#             */
/*   Updated: 2023/10/31 16:55:57 by druina           ###   ########.fr       */
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
	char	*tmp;
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

// checks that the number is between 0 and 255
static int convert_color_value_to_int(char *value)
{
	int result;

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

	i = 0;
	tmp = ft_split(line, ',');
	if (!tmp)
		dt_error(MALLOC_FAIL); // change error message
	while (tmp[i])
	{
		if (i >= 3) // if there is more colors
			dt_error(INVALID_COLOR);
		rgb[i] = convert_color_value_to_int(tmp[i]);
		i++;
	}
	if (i < 3) // if there is less colors
		dt_error(INVALID_COLOR);
	free_2d(tmp);
	return (get_rgba(rgb[0], rgb[1], rgb[2], 1));
}

// checks which functions should be called
int	store_map_params(char **line, t_map *map)
{
	char	*tmp;

	tmp = ft_strtrim(*line, " \t");
	if (!tmp)
		dt_error(MALLOC_FAIL);
	free(*line);
	*line = tmp;
	if (!ft_strncmp(*line, "SO ", 3))
		return(map->textures.so = get_texture(*line + 2), 42);
	if (!ft_strncmp(*line, "NO ", 3))
		return(map->textures.no = get_texture(*line + 2), 42);
	if (!ft_strncmp(*line, "WE ", 3))
		return(map->textures.we = get_texture(*line + 2), 42);
	if (!ft_strncmp(*line, "EA ", 3))
		return(map->textures.ea = get_texture(*line + 2), 42);
	if (!ft_strncmp(*line, "F ", 2))
		return(map->floor_color = get_color(*line + 1), 42);
	if (!ft_strncmp(*line, "C ", 2))
		return(map->cealing_color = get_color(*line + 1), 42);
	if (**line == '\n')
		return (42);
	dt_error(INVALID_MAP);
	return (42);
}
