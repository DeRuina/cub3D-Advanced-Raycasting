/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_colors.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:44:44 by tspoof            #+#    #+#             */
/*   Updated: 2023/10/05 14:44:52 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_COLORS_H
# define MLX_COLORS_H

// 'Encodes' four individual bytes into an int.
int	get_rgba(int r, int g, int b, int a);

// Get the red channel.
int	get_r(int rgba);

// Get the green channel.
int	get_g(int rgba);

// Get the blue channel.
int	get_b(int rgba);

// Get the alpha channel.
int	get_a(int rgba);

#endif
