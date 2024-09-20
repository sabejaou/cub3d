/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabejaou <sabejaou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 01:04:57 by sabejaou          #+#    #+#             */
/*   Updated: 2024/09/20 02:40:16 by sabejaou         ###   ########.fr       */
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

void	draw_line(t_vec3x1 *start, t_vec3x1 *end, t_view *view, int col)
{
	t_drawlineutils u;

	u.i = 0;
	u.dx = end->x - start->x;
	u.dy = end->y - start->y;
	if (fabs(u.dx) > fabs(u.dy))
		u.steps = fabs(u.dx);
	else
		u.steps = fabs(u.dy);
	u.x_inc = u.dx / (float)u.steps;
	u.y_inc = u.dy / (float)u.steps;
	u.x = start->x;
	u.y = start->y;
	while (u.i <= u.steps)
	{
		if (u.x >= 0 && u.y >= 0 && u.x < WINDOW_WIDTH - 4
			&& u.y < WINDOW_HEIGHT - 4)
			((int *)view->addr)[(int)u.y * (view->sl >> 2)
				+ (int)u.x] = col;
		u.x += u.x_inc;
		u.y += u.y_inc;
		u.i++;
	}
}

void	drawsquare(t_vec3x1 start, t_view *view, int col, int sqprp)
{
	int x;
	int y;
	t_vec3x1 end;
	t_vec3x1 tmp;

	x = 0;
	y = 0;
	tmp.x = start.x;
	tmp.y = start.y;
	while (y <= sqprp)
	{
		end.x = start.x + sqprp;
		end.y = tmp.y;
		draw_line(&tmp, &end, view, col);
		tmp.y += 1;
		y++;
	}
}

void	draw2dmap(t_view *view)
{
	int squareproportion;
	size_t y;
	int tmpx;
	int tmpy;
	size_t x;

	y = 0;
	x = 0;
	tmpx = 0;
	tmpy = 0;
	view->map.tab[y][x].y = 0;
	if (view->map.maxy >= view->map.maxx)
		squareproportion = WINDOW_HEIGHT / view->map.maxy;
	else
		squareproportion = WINDOW_HEIGHT / view->map.maxx;
	printf("sqrprp:%d\n", squareproportion);
	while(y < view->map.maxy)
	{
		view->map.tab[y][x].x = 0;
		tmpx = view->map.tab[y][x].x;
		while (x < view->map.maxx)
		{
			// printf("1x:%f y:%f\n", view->map.tab[y][x].x, view->map.tab[y][x].y);
			if (view->map.tab[y][x].type == WALL)
				drawsquare(view->map.tab[y][x],  view, 0XFF0000, squareproportion);
			tmpx += squareproportion;
			x++;
			if (x < view->map.maxx)
			{
				view->map.tab[y][x].x = tmpx;
				view->map.tab[y][x].y = tmpy;
			}
		}
		tmpy += squareproportion;
		y++;
		x = 0;
		if (y < view->map.maxy)
			view->map.tab[y][x].y = tmpy;
	}
	mlx_put_image_to_window(view->mlx_ptr, view->win_ptr, view->img, 0, 0);
	printf("playerx:%f playery:%f\n", view->player.x, view->player.y);
}

int	key_press(int keycode, t_view *view)
{
	int squareproportion;
	
	if (view->map.maxy >= view->map.maxx)
		squareproportion = WINDOW_HEIGHT / view->map.maxy;
	else
		squareproportion = WINDOW_HEIGHT / view->map.maxx;
	if (keycode == W_KEY)
		view->player.y *= 0.99;
	else if (keycode == S_KEY)
		view->player.y *= 1.01;
	else if (keycode == A_KEY)
		view->player.x *= 0.99;
	else if (keycode == D_KEY)
		view->player.x *= 1.01;
	else if (keycode == ESC_KEY)
		ft_free_map_end_normal(view);
	mlx_destroy_image(view->mlx_ptr, view->img);
	view->player_img = mlx_new_image(view->mlx_ptr, squareproportion, squareproportion);
	view->player_addr = mlx_get_data_addr(view->player_img, &view->bpp, &view->sl,
			&view->endian);
	drawsquare(view->player,  view, 0X0000FF, squareproportion);
	mlx_put_image_to_window(view->mlx_ptr, view->win_ptr, view->player_img, 0, 0);
	// drawplayer(view);
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
	int squareproportion;
	
	view = ft_calloc(1, sizeof(t_view));
	err = NO_ERROR;
	if (ac != 2)
		return(ft_error(ERR_ARGS_NBR, view));
	err = init_view(view, av);
	if (err)
		return (err);
	if (view->map.maxy >= view->map.maxx)
		squareproportion = WINDOW_HEIGHT / view->map.maxy;
	else
		squareproportion = WINDOW_HEIGHT / view->map.maxx;
	printf("%f %f\n", view->player.x, view->player.y);
	view->player.x *= squareproportion;
	view->player.y *= squareproportion;
	draw2dmap(view);
	mlx_hook(view->win_ptr, 2, 1L << 0, (int (*)())key_press, view);
	mlx_hook(view->win_ptr, 17, 0, (int (*)())ft_free_map_end_normal, view);
	mlx_loop(view->mlx_ptr);
	// ft_free_map(view);
}
