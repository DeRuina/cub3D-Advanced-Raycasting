/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 10:05:09 by druina            #+#    #+#             */
/*   Updated: 2023/10/23 12:52:22 by tspoof           ###   ########.fr       */
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


typedef enum e_error
{
	MALLOC_FAIL,
	WRONG_AMOUNT,
	FILE_TYPE,
	FILE_OPEN,
	INVALID_MAP,
	INVALID_COLOR,
	INVALID_TEXTURE
} t_error;

typedef struct s_textures
{
	mlx_texture_t		*no;
	mlx_texture_t		*so;
	mlx_texture_t		*we;
	mlx_texture_t		*ea;
}				t_textures;

typedef struct s_map
{
	int			floor_color;
	int			cealing_color;
	t_textures	textures;
}				t_map;

int				parse_map(char *path, t_map *map);

#endif
