/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabejaou <sabejaou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 08:12:13 by sabejaou          #+#    #+#             */
/*   Updated: 2024/10/07 16:57:44 by sabejaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

#include "../incl/cub3d.h"

void	load_textures(t_view *view)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		view->textures[i] = mlx_xpm_file_to_image(view->mlx_ptr, view->text[i],
				&view->texture_width[i], &view->texture_height[i]);
		if (!view->textures[i])
		{
			fprintf(stderr, "Error loading texture: %s\n", view->text[i]);
			exit(EXIT_FAILURE);
		}
		i++;
	}
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
	printf("PLAYERTYPE:%d\n", view->player.type);
	if (view->player.type == SPAWN_NORTH)
		view->playerangle = 3 * M_PI / 2;
	else if (view->player.type == SPAWN_SOUTH)
		view->playerangle = M_PI / 2;
	else if (view->player.type == SPAWN_WEST)
		view->playerangle = M_PI;
	else
		view->playerangle = 0;
	load_textures(view);
	return (err);
}
