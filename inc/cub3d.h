/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 10:05:09 by druina            #+#    #+#             */
/*   Updated: 2023/11/15 12:58:07 by tspoof           ###   ########.fr       */
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

# define HEIGHT 512
# define WIDTH 512

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
	NO_PLAYER,
	MLX_ERROR
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
	int			max_height;
	int			max_width;
	int			floor_color;
	int			cealing_color;
	t_textures	textures;
	t_vec		*map;
}				t_map;

typedef struct s_player
{
	float	x;
	float	y;
	float	delta_x;
	float	delta_y;
	float	angle;
}				t_player;


typedef struct s_cub
{
	t_map *map;
	mlx_t *mlx;
	mlx_image_t *image;
	t_player	*player;
}				t_cub;

int				parse_map(char *path, t_map *map);
void			dt_error(int err_no);
void			store_map(char *line, t_map *map);
int				store_map_params(char **line, t_map *map);
// int				is_precent(int *item);
void			draw(void *param);

// parse_map.c
int				is_player(char c);

#endif
