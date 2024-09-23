/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabejaou <sabejaou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 08:06:55 by sabejaou          #+#    #+#             */
/*   Updated: 2024/09/23 10:17:34 by sabejaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

void	calculate_step_and_ray_length(t_ray_data *data, t_vector2f player_pos)
{
	if (data->ray_dir.x < 0)
	{
		data->step.x = -1;
		data->ray_length_1d.x = (player_pos.x - data->map_check.x)
			* data->step_size.x;
	}
	else
	{
		data->step.x = 1;
		data->ray_length_1d.x = (data->map_check.x + 1 - player_pos.x)
			* data->step_size.x;
	}
	if (data->ray_dir.y < 0)
	{
		data->step.y = -1;
		data->ray_length_1d.y = (player_pos.y - data->map_check.y)
			* data->step_size.y;
	}
	else
	{
		data->step.y = 1;
		data->ray_length_1d.y = (data->map_check.y + 1 - player_pos.y)
			* data->step_size.y;
	}
}

int	check_wall_hit(t_ray_data *data, t_view *view)
{
	if (data->map_check.x < 0 || data->map_check.x >= view->map.maxx)
		return (1);
	if (data->map_check.y < 0 || data->map_check.y >= view->map.maxy)
		return (1);
	if (view->map.tab[(int)data->map_check.y]
		[(int)data->map_check.x].type == WALL)
	{
		if (data->hit_vertical)
		{
			if (data->step.x > 0)
				data->texture_index = 3;
			else
				data->texture_index = 2;
		}
		else
		{
			if (data->step.y > 0)
				data->texture_index = 1;
			else
				data->texture_index = 0;
		}
		return (1);
	}
	return (0);
}

void	perform_dda(t_ray_data *data, t_view *view)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (data->ray_length_1d.x < data->ray_length_1d.y)
		{
			data->map_check.x += data->step.x;
			data->distance = data->ray_length_1d.x * 0.1;
			data->ray_length_1d.x += data->step_size.x;
			data->hit_vertical = 1;
		}
		else
		{
			data->map_check.y += data->step.y;
			data->distance = data->ray_length_1d.y * 0.1;
			data->ray_length_1d.y += data->step_size.y;
			data->hit_vertical = 0;
		}
		hit = check_wall_hit(data, view);
	}
}

t_raycast_hit	calculate_hit_point(t_ray_data *data, t_vector2f player_pos,
		int squareproportion)
{
	float	exact_hit_x;
	float	exact_hit_y;
	float	wall_x;

	if (data->hit_vertical)
	{
		exact_hit_x = data->map_check.x;
		exact_hit_y = player_pos.y + (data->map_check.x - player_pos.x)
			* data->ray_dir.y / data->ray_dir.x;
		wall_x = exact_hit_y - floor(exact_hit_y);
	}
	else
	{
		exact_hit_y = data->map_check.y;
		exact_hit_x = player_pos.x + (data->map_check.y - player_pos.y)
			* data->ray_dir.x / data->ray_dir.y;
		wall_x = exact_hit_x - floor(exact_hit_x);
	}
	return ((t_raycast_hit){data->distance * squareproportion,
		data->texture_index, wall_x,
		(int)data->map_check.x, (int)data->map_check.y});
}

t_raycast_hit	cast_ray(t_view *view, t_vector2f player_pos,
		float angle, int squareproportion)
{
	t_ray_data	data;

	init_ray_data(&data, player_pos, angle);
	calculate_step_and_ray_length(&data, player_pos);
	perform_dda(&data, view);
	return (calculate_hit_point(&data, player_pos, squareproportion));
}
