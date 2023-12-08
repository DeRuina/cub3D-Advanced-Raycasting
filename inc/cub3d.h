/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 10:05:09 by druina            #+#    #+#             */
/*   Updated: 2023/12/08 13:27:38 by druina           ###   ########.fr       */
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

# define HEIGHT 1024
# define WIDTH 1024
# define TEX_W 64
# define TEX_H 64

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
}					t_error;

typedef struct s_textures
{
	mlx_texture_t	*no;
	mlx_texture_t	*so;
	mlx_texture_t	*we;
	mlx_texture_t	*ea;
}					t_textures;

typedef struct s_map
{
	int				max_height;
	int				max_width;
	int				floor_color;
	int				cealing_color;
	t_textures		textures;
	t_vec			*map;
}					t_map;

typedef struct s_player
{
	double			x;
	double			y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			move_speed;
	double			rot_speed;

}					t_player;

typedef struct s_ray
{
	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
	int				map_x;
	int				map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_wall_dist;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	int				line_height;
	int				draw_start;
	int				draw_end;
}					t_ray;

typedef struct s_cub
{
	t_map			*map;
	mlx_t			*mlx;
	mlx_image_t		*image;
	t_player		*player;
	t_ray			*ray;
}					t_cub;

t_cub				cub_init(void);
void				cub_destroy(t_cub *cub);

int					parse_map(char *path, t_cub *cub);
void				dt_error(int err_no);
void				store_map(char *line, t_map *map);
int					store_map_params(char **line, t_map *map);
int					is_player(char c);

void				render(t_cub *cub);
void				cast_ray(int x, t_cub *cub);
void				draw_wall(int x, t_cub *cub);

#endif
