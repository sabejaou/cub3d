/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabejaou <sabejaou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 08:00:43 by sabejaou          #+#    #+#             */
/*   Updated: 2024/09/23 09:33:50 by sabejaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int	check_collision(t_move_data *data, t_view *view)
{
	int		map_x;
	int		map_y;
	int		dy;
	int		dx;

	map_x = data->new_x / data->squareproportion;
	map_y = data->new_y / data->squareproportion;
	dy = -1;
	while (dy <= 1)
	{
		dx = -1;
		while (dx <= 1)
		{
			if (check_wall_collision(data, view, map_x + dx, map_y + dy))
				return (1);
			dx++;
		}
		dy++;
	}
	return (0);
}

void	update_player_position(t_view *view, t_move_data *data)
{
	view->player.x = data->new_x;
	view->player.y = data->new_y;
}

void	handle_rotation(t_view *view, int keycode)
{
	if (keycode == A_ARROW_KEY)
		view->playerangle -= ROTATE_SPEED;
	else if (keycode == D_ARROW_KEY)
		view->playerangle += ROTATE_SPEED;
}

void	update_display(t_view *view, int squareproportion)
{
	mlx_destroy_image(view->mlx_ptr, view->img);
	view->img = mlx_new_image(view->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	view->addr = mlx_get_data_addr(view->img,
			&view->bpp, &view->sl, &view->endian);
	fill_background(view);
	ft_draw3d_view(view, squareproportion);
	view->addr = mlx_get_data_addr(view->img,
			&view->bpp, &view->sl, &view->endian);
	draw_minimap(view, squareproportion);
	mlx_put_image_to_window(view->mlx_ptr, view->win_ptr, view->img, 0, 0);
}

int	key_press(int keycode, t_view *view)
{
	t_move_data	data;

	init_move_data(&data, view);
	if (keycode == W_KEY || keycode == S_KEY
		|| keycode == A_KEY || keycode == D_KEY)
	{
		calculate_new_position(&data, view, keycode);
		if (!check_collision(&data, view))
			update_player_position(view, &data);
	}
	else if (keycode == A_ARROW_KEY || keycode == D_ARROW_KEY)
		handle_rotation(view, keycode);
	else if (keycode == ESC_KEY)
		ft_free_map_end_normal(view);
	update_display(view, data.squareproportion);
	return (0);
}
