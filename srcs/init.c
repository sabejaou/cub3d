/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsofien- <tsofien-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 08:12:13 by sabejaou          #+#    #+#             */
/*   Updated: 2024/10/19 20:07:27 by tsofien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	init_vmapcols(t_vmapcols *a, int *fd, char **line)
{
	a->i = 0;
	a->err = NO_ERROR;
	ft_strlcpy(a->compass[0], "F ", 3);
	ft_strlcpy(a->compass[1], "C ", 3);
	while (ft_str_is_whitespace(*line))
		*line = get_next_line(*fd, *line, 0);
	if (!ft_strncmp(*line, a->compass[1], 2))
		a->i = 1;
	a->sense = (bool)a->i;
}

t_errcd	load_textures(t_view *view)
{
	int	i;

	i = 0;
	if (!view->txtvrf.ea || !view->txtvrf.we || !view->txtvrf.so
		|| !view->txtvrf.no)
	{
		ft_putendl_fd("Cub3d: MLX_ERROR: NOT ALL DIRECTIONS TEXTURES\n", 2);
		ft_free_map_end_normal(view);
	}
	while (i < 4)
	{
		view->textures[i] = mlx_xpm_file_to_image(view->mlx_ptr, view->text[i],
				&view->texture_width[i], &view->texture_height[i]);
		if (!view->textures[i])
		{
			ft_putendl_fd("Cub3d: MLX_ERROR : XPM TRANSFORMATION\n", 2);
			ft_free_map_end_normal(view);
		}
		i++;
	}
	return (NO_ERROR);
}

t_errcd	ft_init_verify_map(char **av, t_view *view)
{
	t_errcd	err;

	err = NO_ERROR;
	err = ft_create_map(av[1], view);
	if (err != NO_ERROR)
		return (ft_error(err, view));
	err = ft_scanmap(view->map);
	if (err != NO_ERROR)
		return (ft_error(err, view));
	return (err);
}

void	setplayerangle(t_view *view)
{
	view->playerangle = 0;
	if (view->player.type == SPAWN_NORTH)
		view->playerangle = 3 * M_PI / 2;
	else if (view->player.type == SPAWN_SOUTH)
		view->playerangle = M_PI / 2;
	else if (view->player.type == SPAWN_WEST)
		view->playerangle = M_PI;
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
		return (ft_error(ERR_MLX, view), ERR_MLX);
	view->win_ptr = mlx_new_window(view->mlx_ptr,
			WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D - 42");
	if (view->win_ptr == NULL)
		return (ft_error(ERR_MLX, view), ERR_MLX);
	view->img = mlx_new_image(view->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!view->img)
		return (ft_error(ERR_MLX, view), ERR_MLX);
	view->addr = mlx_get_data_addr(view->img, &view->bpp, &view->sl,
			&view->endian);
	setplayerangle(view);
	err = load_textures(view);
	return (err);
}
