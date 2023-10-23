/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 14:31:07 by tspoof            #+#    #+#             */
/*   Updated: 2023/10/23 12:52:22 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	dt_strerror(err_no)
{
	static char	*dt_errors[MLX_ERRMAX] = {
		"Error: malloc failed\n",
		"Error: Wrong amount of arguments\n",
		"Error: Wrong file type\n",
		"Error: File openning failed\n",
		"Error: Invalid map\n",
		"Error: Invalid color\n",
		"Error: Invalid texture\n"
	};
	ft_putstr_fd(dt_errors[err_no], 2);
}

static void	dt_error(int err_no)
{
	dt_strerror(err_no);
	exit(EXIT_FAILURE);
}

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
static void	parse_factory(char **line, t_map *map)
{
	char	*tmp;

	tmp = ft_strtrim(*line, " \t");
	if (!tmp)
		dt_error(MALLOC_FAIL);
	free(*line);
	*line = tmp;
	if (!ft_strncmp(*line, "SO ", 3))
		map->textures.so = get_texture(*line + 2);
	if (!ft_strncmp(*line, "NO ", 3))
		map->textures.no = get_texture(*line + 2);
	if (!ft_strncmp(*line, "WE ", 3))
		map->textures.we = get_texture(*line + 2);
	if (!ft_strncmp(*line, "EA ", 3))
		map->textures.ea = get_texture(*line + 2);
	if (!ft_strncmp(*line, "F ", 2))
		map->floor_color = get_color(*line + 1);
	if (!ft_strncmp(*line, "C ", 2))
		map->cealing_color = get_color(*line + 1);
}

// ceiling and floor colour 0 is acceptable


void check_map_values(t_map *map)
{
	if (map->cealing_color < 0 || map->floor_color < 0)
		dt_error(INVALID_COLOR);
	if (!map->textures.no || !map->textures.we || !map->textures.ea
		 || !map->textures.so)
		 	dt_error(INVALID_TEXTURE);
}

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
		parse_factory(&line, map);
		free(line);
		line = NULL;
	}
	check_map_values(map);
	close(fd);
	return (0);
}
