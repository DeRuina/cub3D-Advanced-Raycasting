/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 15:19:15 by tspoof            #+#    #+#             */
/*   Updated: 2023/12/08 14:35:38 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	dt_strerror(int err_no)
{
	static char	*dt_errors[MLX_ERRMAX] = {
		"EXIT SUCCESS\n",
		"Error: malloc failed\n",
		"Error: Wrong amount of arguments\n",
		"Error: Wrong file type\n",
		"Error: File openning failed\n",
		"Error: Invalid map\n",
		"Error: Invalid color\n",
		"Error: Invalid texture\n",
		"Error: No player\n",
		"Error: mlx failure\n"
	};

	ft_putstr_fd(dt_errors[err_no], 2);
}

void	dt_error(int err_no)
{
	dt_strerror(err_no);
	exit(EXIT_FAILURE);
}
