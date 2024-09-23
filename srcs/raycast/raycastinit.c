/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycastinit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabejaou <sabejaou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 08:07:24 by sabejaou          #+#    #+#             */
/*   Updated: 2024/09/23 10:17:12 by sabejaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

void	init_ray_data(t_ray_data *data, t_vector2f player_pos, float angle)
{
	data->ray_dir.x = cosf(angle);
	data->ray_dir.y = sinf(angle);
	data->step_size.x = sqrtf(1 + (data->ray_dir.y / data->ray_dir.x)
			* (data->ray_dir.y / data->ray_dir.x));
	data->step_size.y = sqrtf(1 + (data->ray_dir.x / data->ray_dir.y)
			* (data->ray_dir.x / data->ray_dir.y));
	data->map_check.x = floorf(player_pos.x);
	data->map_check.y = floorf(player_pos.y);
	data->ray_length_1d.x = 0;
	data->ray_length_1d.y = 0;
	data->step.x = 0;
	data->step.y = 0;
	data->distance = 0;
	data->hit_vertical = 0;
	data->texture_index = 0;
}
