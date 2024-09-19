/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabejaou <sabejaou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 01:04:57 by sabejaou          #+#    #+#             */
/*   Updated: 2024/09/19 02:00:32 by sabejaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	ft_free_map_end_normal(t_view *view)
{
	size_t y;

	y = 0;
	while(view->map.tab && y < view->map.maxy)
	{
			if (view->map.tab[y])
				free(view->map.tab[y]);
			y++;
	}
	y = 0;
	while(y < 4)
	{
		if (view->text[y])
			free(view->text[y]);
		y++;
	}
	if (view->map.tab)
		free(view->map.tab);
	mlx_destroy_image(view->mlx_ptr, view->img);
	mlx_destroy_window(view->mlx_ptr, view->win_ptr);
	mlx_destroy_display(view->mlx_ptr);
	free(view->mlx_ptr);
	if (view)
		free(view);
	exit(0);
}

void	ft_free_map(t_view *view)
{
	size_t y;

	y = 0;
	while(view->map.tab && y < view->map.maxy)
	{
			if (view->map.tab[y])
				free(view->map.tab[y]);
			y++;
	}
	y = 0;
	while(y < 4)
	{
		if (view->text[y])
			free(view->text[y]);
		y++;
	}
	if (view->map.tab)
		free(view->map.tab);
	if (view)
		free(view);
}

int	key_press(int keycode, t_view *view)
{
	if (keycode == W_KEY)
		printf("W PRESSED\n");
	else if (keycode == S_KEY)
		printf("S PRESSED\n");
	else if (keycode == A_KEY)
		printf("A PRESSED\n");
	else if (keycode == D_KEY)
		printf("D PRESSED\n");
	else if (keycode == ESC_KEY)
		ft_free_map_end_normal(view);
	mlx_destroy_image(view->mlx_ptr, view->img);
	view->img = mlx_new_image(view->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	view->addr = mlx_get_data_addr(view->img, &view->bpp, &view->sl,
			&view->endian);
	// draw2dmap(view);
	return (0);
}

int ft_error(t_errcd err, t_view *view)
{
	printf("ERROR:%d\n", err);
	if (err == ERR_ARGS_NBR)
		ft_putendl_fd("Cub3d: Args number invalid\n", 2);
	if (err == ERR_ACCESS_MAP)
		ft_putendl_fd("Cub3d: Can't access path of the map\n", 2);
	if (err == ERR_INVALID_MAP)
		ft_putendl_fd("Cub3d: Map is invalid\n", 2);
	if (err == ERR_FILE_CONSTRUCTION)
		ft_putendl_fd("Cub3d: File is not formated as expected\n", 2);
	if (err == ERR_ACCESS_TEXTURE)
		ft_putendl_fd("Cub3d: Texture file can't be opened\n", 2);
	if (err == ERR_COLOR_FORMAT)
		ft_putendl_fd("Cub3d: Bad colors format\n", 2);
	if (err == ERR_FORMAT_TEXTURE)
		ft_putendl_fd("Cub3d: Bad texture format\n", 2);
	if (err == ERR_ACCESS_MAP)
		ft_putendl_fd("Cub3d: Map can't be opened\n", 2);
	if (err == ERR_EXTENSION_MAP)
		ft_putendl_fd("Cub3d: Map extension is wrong\n", 2);
	if (err == ERR_MLX)
		ft_putendl_fd("Cub3d: MLX_ERROR\n", 2);
	if (err != NO_ERROR)
		ft_free_map(view);
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
		x = 0;
	}
}

t_errcd ft_init_verify_map(char **av, t_view *view)
{
	t_errcd	err;
	
	err = NO_ERROR;
	err = ft_create_map(av[1], view);
	if (err != NO_ERROR)
		return (ft_error(err, view));
	ft_print_map_types(view);
	err = ft_scanmap(view->map);
	if (err != NO_ERROR)
		return (ft_error(err, view));
	return (err);
	
}
t_errcd	init_view(t_view *view, char **av)
{
	t_errcd	err;
	
	err = NO_ERROR;
	err = ft_init_verify_map(av, view);
	if (err)
		return (err);
	view->mlx_ptr = mlx_init();
	if (view->mlx_ptr == NULL)
		return (ERR_MLX);
	view->win_ptr = mlx_new_window(view->mlx_ptr,
			WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D - 42");
	if (view->win_ptr == NULL)
		return (ERR_MLX);
	view->img = mlx_new_image(view->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	view->addr = mlx_get_data_addr(view->img, &view->bpp, &view->sl,
			&view->endian);
	return(err);
}

int	main(int ac, char **av)
{
	t_view *view;
	t_errcd	err;
	
	view = ft_calloc(1, sizeof(t_view));
	err = NO_ERROR;
	if (ac != 2)
		return(ft_error(ERR_ARGS_NBR, view));
	err = init_view(view, av);
	if (err)
		return (err);
	mlx_hook(view->win_ptr, 2, 1L << 0, (int (*)())key_press, view);
	mlx_hook(view->win_ptr, 17, 0, (int (*)())ft_free_map_end_normal, view);
	mlx_loop(view->mlx_ptr);
	// ft_free_map(view);
}
