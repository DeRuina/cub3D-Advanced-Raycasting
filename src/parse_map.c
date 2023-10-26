/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 14:31:07 by tspoof            #+#    #+#             */
/*   Updated: 2023/10/23 16:43:14 by tspoof           ###   ########.fr       */
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
static int	call_appropriate_func(char **line, t_map *map)
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


int valid_colors(t_map *map)
{
	if (map->cealing_color < 0 || map->floor_color < 0)
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

int	valid_map_chars(char *line)
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
		(void)call_appropriate_func(&line, map);
		free(line);
		line = NULL;
		if (valid_colors(map) && valid_textures(map))
			break;
	}
	while ((line = get_next_line(fd)))
	{
		// skip till the map starts
		store_map(line, map);
		free(line);
		line = NULL;
	}
	// check_map_values(map);
	// new open and loop
	close(fd);
	return (0);
}
