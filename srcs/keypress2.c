/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabejaou <sabejaou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 08:39:15 by sabejaou          #+#    #+#             */
/*   Updated: 2024/10/17 14:39:33 by sabejaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

int	check_wall_collision(t_move_data *data, t_view *view,
	size_t check_x, size_t check_y)
{
	if (check_x < view->map.maxx && check_y < view->map.maxy)
	{
		if (view->map.tab[check_y][check_x].type == WALL)
		{
			if (is_collision(data, check_x, check_y))
				return (1);
		}
	}
	return (0);
}

void	init_move_data(t_move_data *data, t_view *view)
{
	if (view->map.maxy >= view->map.maxx)
		data->squareproportion = WINDOW_HEIGHT / view->map.maxy;
	else
		data->squareproportion = WINDOW_HEIGHT / view->map.maxx;
	data->move_speed = 5.0f;
	data->hitbox_radius = data->squareproportion * 0.09f;
	data->new_x = view->player.x;
	data->new_y = view->player.y;
}

void	calculate_new_position(t_move_data *data, t_view *view, int keycode)
{
	if (keycode == W_KEY)
	{
		data->new_x += cos(view->playerangle) * data->move_speed;
		data->new_y += sin(view->playerangle) * data->move_speed;
	}
	else if (keycode == S_KEY)
	{
		data->new_x -= cos(view->playerangle) * data->move_speed;
		data->new_y -= sin(view->playerangle) * data->move_speed;
	}
	else if (keycode == A_KEY)
	{
		data->new_x += sin(view->playerangle) * data->move_speed;
		data->new_y -= cos(view->playerangle) * data->move_speed;
	}
	else if (keycode == D_KEY)
	{
		data->new_x -= sin(view->playerangle) * data->move_speed;
		data->new_y += cos(view->playerangle) * data->move_speed;
	}
}

int	is_collision(t_move_data *data, size_t check_x, size_t check_y)
{
	float	wall_center_x;
	float	wall_center_y;
	float	dx;
	float	dy;
	float	distance;

	wall_center_x = (check_x + 0.5f) * data->squareproportion;
	wall_center_y = (check_y + 0.5f) * data->squareproportion;
	dx = fmaxf(fabsf(data->new_x - wall_center_x)
			- data->squareproportion / 2, 0);
	dy = fmaxf(fabsf(data->new_y - wall_center_y)
			- data->squareproportion / 2, 0);
	distance = sqrtf(dx * dx + dy * dy);
	if (distance <= data->hitbox_radius)
		return (1);
	return (0);
}
