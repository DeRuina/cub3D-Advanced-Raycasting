/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 10:02:10 by druina            #+#    #+#             */
/*   Updated: 2023/10/03 14:39:52 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (ft_putstr_fd("Wrong amount of arguments", 2), 1);
	if (ft_strlen(ft_strnstr(argv[1], ".cub", ft_strlen(argv[1]))) != 4)
		return(ft_putstr_fd("Wrong file type", 2), 1);
	if (!parse_map(argv[1]))
		return(ft_putstr_fd("Invalid map", 2), 2);

	argc = 0;
	argv = NULL;
	return (0);
}