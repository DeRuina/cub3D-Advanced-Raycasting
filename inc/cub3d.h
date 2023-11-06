/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 10:05:09 by druina            #+#    #+#             */
/*   Updated: 2023/11/06 15:17:28 by tspoof           ###   ########.fr       */
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
	CORRECT,
	MALLOC_FAIL,
	WRONG_AMOUNT,
	FILE_TYPE,
	FILE_OPEN,
	INVALID_MAP,
	INVALID_COLOR,
	INVALID_TEXTURE,
	NO_PLAYER
} t_error;

typedef struct s_present
{
	int NO;
	int	SO;
	int WE;
	int EA;
	int F;
	int C;
}				t_present;

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
	t_vec		*map;
	t_present	s_present;
}				t_map;

int				parse_map(char *path, t_map *map);
void			dt_error(int err_no);
void			store_map(char *line, t_map *map);
int				store_map_params(char **line, t_map *map);

#endif
