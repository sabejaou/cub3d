/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3dmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabejaou <sabejaou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 07:57:42 by sabejaou          #+#    #+#             */
/*   Updated: 2024/09/23 08:28:44 by sabejaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

void	init_draw_data(t_draw_data *data, t_view *view, int squareproportion)
{
	data->player_pos.x = view->player.x / squareproportion;
	data->player_pos.y = view->player.y / squareproportion;
	data->fov = M_PI / 3;
	data->ray_step = data->fov / WINDOW_WIDTH;
	data->squareproportion = squareproportion;
}

void	calculate_ray_result(t_ray_result *result, RaycastHit hit,
		float ray_angle, t_view *view)
{
	result->perp_distance = hit.distance * cosf(ray_angle - view->playerangle);
	result->line_height = (int)(WINDOW_HEIGHT / result->perp_distance);
	result->draw_start = -result->line_height / 2 + WINDOW_HEIGHT / 2;
	result->draw_end = result->line_height / 2 + WINDOW_HEIGHT / 2;
	if (result->draw_start < 0)
		result->draw_start = 0;
	if (result->draw_end >= WINDOW_HEIGHT)
		result->draw_end = WINDOW_HEIGHT - 1;
	result->tex_x = (int)(hit.wall_x * view->texture_width[hit.texture_index]);
	if (hit.texture_index == 2 || hit.texture_index == 3)
		result->tex_x = view->texture_width[hit.texture_index]
			- result->tex_x - 1;
	result->step = 1.0 * view->texture_height[hit.texture_index]
		/ result->line_height;
	result->tex_pos = (result->draw_start - WINDOW_HEIGHT
			/ 2 + result->line_height / 2)
		* result->step;
}

void	draw_vertical_line(t_view *view, t_ray_result *result, int x,
		int texture_index)
{
	int	y;
	int	tex_y;
	int	*texture_data;
	int	color;

	y = result->draw_start;
	while (y <= result->draw_end)
	{
		tex_y = (int)result->tex_pos
			& (view->texture_height[texture_index] - 1);
		result->tex_pos += result->step;
		texture_data = (int *)mlx_get_data_addr(view->textures[texture_index],
				&view->bpp, &view->sl, &view->endian);
		color = texture_data[tex_y * view->texture_width[texture_index]
			+ result->tex_x];
		view->addr = mlx_get_data_addr(view->img, &view->bpp, &view->sl,
				&view->endian);
		((int *)view->addr)[y * (view->sl >> 2) + x] = color;
		y++;
	}
}

void	ft_draw3d_view(t_view *view, int squareproportion)
{
	t_draw_data		data;
	t_ray_result	result;
	int				x;
	float			ray_angle;
	RaycastHit		hit;

	init_draw_data(&data, view, squareproportion);
	view->addr = mlx_get_data_addr(view->img, &view->bpp, &view->sl,
			&view->endian);
	x = 0;
	while (x < WINDOW_WIDTH)
	{
		ray_angle = view->playerangle - data.fov / 2 + x * data.ray_step;
		hit = cast_ray(view, data.player_pos, ray_angle, data.squareproportion);
		calculate_ray_result(&result, hit, ray_angle, view);
		draw_vertical_line(view, &result, x, hit.texture_index);
		x++;
	}
}
