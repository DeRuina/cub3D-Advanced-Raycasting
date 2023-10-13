/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 14:31:07 by tspoof            #+#    #+#             */
/*   Updated: 2023/10/13 16:44:01 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	dt_strerror(err_no)
{
	static char	*dt_errors[MLX_ERRMAX] = {
		"Error: Wrong amount of arguments\n",
		"Error: Wrong file type\n",
		"Error: File openning failed\n",
		"Error: Invalid map\n",
		"Error: Invalid color\n"
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

static xpm_t	*get_texture(char *line)
{
	char	*tmp;
	xpm_t	*result;

	tmp = ft_strtrim(line, " \t\n");
	if (!tmp)
		return (NULL);
	result = mlx_load_xpm42(tmp);
	free(tmp);
	if (!result)
		mlx_error();
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
		return (0);
	while (tmp[i])
	{
		if (i >= 3)
			dt_error(4);
		rgb[i] = ft_atoi(tmp[i]);
		if (rgb[i] < 0)
			dt_error(4);
		i++;
	}
	if (i < 3)
		dt_error(4);
	return (get_rgba(rgb[0], rgb[1], rgb[2], 1));
}

int	parse_factory(char **line, t_map *map)
{
	char	*tmp;

	tmp = ft_strtrim(*line, " \t");
	if (!tmp)
		return (1);
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
		map->floor_color = get_color(*line);
	if (!ft_strncmp(*line, "C ", 2))
		map->cealing_color = get_color(*line);
	return (0);
	// checks which functions should be called
}

int	parse_map(char *path, t_map *map)
{
	int		fd;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		dt_error(2);
	line = NULL;
	while ((line = get_next_line(fd)))
	{
		if (parse_factory(&line, map))
		{
			free(line);
			return (1);
		}
		free(line);
	}
	close(fd);
	return (0);
}
