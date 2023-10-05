/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 10:05:09 by druina            #+#    #+#             */
/*   Updated: 2023/10/05 14:45:12 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/MLX42.h"
# include "libft.h"
# include "mlx_colors.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>

typedef struct s_textures
{
	xpm_t		*no;
	xpm_t		*so;
	xpm_t		*we;
	xpm_t		*ea;
}				t_textures;

typedef struct s_map
{
	int			floor_color;
	int			cealing_color;
	t_textures	textures;
}				t_map;

int				parse_map(char *path, t_map *map);

#endif
