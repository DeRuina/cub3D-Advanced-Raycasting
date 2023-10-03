/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 10:05:09 by druina            #+#    #+#             */
/*   Updated: 2023/10/03 16:04:05 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx42.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>

typedef struct s_textures
{
	mlx_texture_t *no;
	mlx_texture_t *so;
	mlx_texture_t *we;
	mlx_texture_t *ea;
} t_textures;

typedef struct	s_map
{
	int	floor_color;
	int	cealing_color;
	t_textures textures;
}				t_map;

int	parse_map(char *path);

#endif
