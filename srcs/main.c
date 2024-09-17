/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabejaou <sabejaou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 01:04:57 by sabejaou          #+#    #+#             */
/*   Updated: 2024/09/17 22:03:44 by sabejaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int ft_error(t_errcd err)
{
	printf("ERROR:%d\n", err);
	if (err == ERR_ARGS_NBR)
		ft_putendl_fd("Cub3d: Args number invalid\n", 2);
	if (err == ERR_ACCESS_MAP)
		ft_putendl_fd("Cub3d: Can't access path of the map\n", 2);
	return (err);
}

void	ft_print_map_types(t_view *view)
{
	size_t x;
	size_t y;

	x = 0;
	y = 0;
	while(y < view->map.maxy)
	{
		while (x < view->map.maxx)
		{
			printf("%d", view->map.tab[y][x].type);
			x++;
		}
		printf("\n");
		y++;
	}
}

int	main(int ac, char **av)
{
	t_view view;
	t_errcd	err;
	err = NO_ERROR;
	if (ac != 2)
		return(ft_error(ERR_ARGS_NBR));
	err = ft_create_map(av[1], &view);
	ft_print_map_types(&view);
	if (err != NO_ERROR)
		return (ft_error(err));
}
