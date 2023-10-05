/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 14:31:07 by tspoof            #+#    #+#             */
/*   Updated: 2023/10/05 12:19:11 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static xpm_t	*get_texture(char *line)
{
	char	*tmp;

	tmp = ft_strtrim(line, " \t");
	if (!tmp)
		return (NULL);
	free(tmp);
	return (mlx_load_xpm42(tmp));
}

int	parse_factory(char *line, t_map *map)
{
	char	*tmp;

	tmp = ft_strtrim(line, " \t");
	if (!tmp)
		return (1);
	free(line);
	line = tmp;
	if (!ft_strncmp(line[0], "SO", 2))
		map->textures.so = get_texture(line + 2);
	if (line[0] == 'N')
		map->textures.no = get_texture(line + 2);
	if (line[0] == 'W')
		map->textures.we = get_texture(line + 2);
	if (line[0] == 'E')
		map->textures.ea = get_texture(line + 2);
	if (line[0] == 'F')
		;
	if (line[0] == 'C')
		;
	// checks which functions should be called
}

int	parse_map(char *path, t_map *map)
{
	int		fd;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd("File openning failed\n", 2), 1);
	while ((line = get_next_line(fd)))
	{
		if (!line)
			break ;
		if (parse_factory(line, map))
			return (1);
		free(line);
	}
	close(fd);
	return (0);
}
