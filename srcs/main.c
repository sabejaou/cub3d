/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsofien- <tsofien-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 01:04:57 by sabejaou          #+#    #+#             */
/*   Updated: 2024/10/19 19:59:46 by tsofien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	ft_free_2(t_view *view)
{
	if (!view->mlx_ptr)
		return ;
	if (view->img)
		mlx_destroy_image(view->mlx_ptr, view->img);
	if (view->win_ptr)
		mlx_destroy_window(view->mlx_ptr, view->win_ptr);
	mlx_destroy_display(view->mlx_ptr);
	free(view->mlx_ptr);
}

void	ft_free_map_end_normal(t_view *view)
{
	size_t	y;

	y = 0;
	while (view->map.tab && y < view->map.maxy)
	{
		if (view->map.tab[y])
			free(view->map.tab[y]);
		y++;
	}
	y = 0;
	while (y < 4)
	{
		if (view->text[y])
			free(view->text[y]);
		if (view->textures[y])
			mlx_destroy_image(view->mlx_ptr, view->textures[y]);
		y++;
	}
	if (view->map.tab)
		free(view->map.tab);
	ft_free_2(view);
	if (view)
		free(view);
	exit(0);
}

void	ft_free_map(t_view *view)
{
	size_t	y;

	y = 0;
	while (view->map.tab && y < view->map.maxy)
	{
		if (view->map.tab[y])
			free(view->map.tab[y]);
		y++;
	}
	y = 0;
	while (y < 4)
	{
		if (view->text[y])
			free(view->text[y]);
		y++;
	}
	ft_free_2(view);
	if (view->map.tab)
		free(view->map.tab);
	if (view)
		free(view);
}

int	ft_error(t_errcd err, t_view *view)
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
	if (err != NO_ERROR && view)
		ft_free_map(view);
	view = NULL;
	return (err);
}

int	main(int ac, char **av)
{
	t_view	*view;
	t_errcd	err;
	int		squareproportion;

	view = ft_calloc(1, sizeof(t_view));
	err = NO_ERROR;
	if (ac != 2)
		return (ft_error(ERR_ARGS_NBR, view));
	err = init_view(view, av);
	if (err)
		return (err);
	squareproportion = WINDOW_HEIGHT / view->map.maxx;
	if (view->map.maxy >= view->map.maxx)
		squareproportion = WINDOW_HEIGHT / view->map.maxy;
	view->player.x *= squareproportion;
	view->player.y *= squareproportion;
	fill_background(view);
	ft_draw3d_view(view, squareproportion);
	view->addr = mlx_get_data_addr(view->img, &view->bpp, &view->sl,
			&view->endian);
	draw_minimap(view, squareproportion);
	mlx_put_image_to_window(view->mlx_ptr, view->win_ptr, view->img, 0, 0);
	mlx_hook(view->win_ptr, 2, 1L << 0, (int (*)())key_press, view);
	mlx_hook(view->win_ptr, 17, 0, (int (*)())ft_free_map_end_normal, view);
	mlx_loop(view->mlx_ptr);
}
