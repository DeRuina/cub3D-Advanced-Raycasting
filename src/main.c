/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 10:02:10 by druina            #+#    #+#             */
/*   Updated: 2023/10/05 15:36:28 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_map	map;

	(void)argc;
	(void)argv;
	parse_map("./test/maps/good/library.cub", &map);
	// if (argc != 2)
	 	//dt_error(0);
	// if (ft_strlen(ft_strnstr(argv[1], ".cub", ft_strlen(argv[1]))) != 4)
	// dt_error(1);
	// if (parse_map(argv[1], &map))
	// 	dt_error(3);
	// argc = 0;
	// argv = NULL;
	return (0);
}
