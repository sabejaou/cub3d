/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawminimap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabejaou <sabejaou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 08:02:36 by sabejaou          #+#    #+#             */
/*   Updated: 2024/09/23 08:25:39 by sabejaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

void	draw_minimap_background(t_view *view, t_minimap_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->minimap_height)
	{
		x = 0;
		while (x < data->minimap_width)
		{
			((int *)view->addr)[(data->start_y + y) * (view->sl >> 2)
				+ (data->start_x + x)] = 0x000000;
			x++;
		}
		y++;
	}
}

void	draw_minimap_walls(t_view *view, t_minimap_data *data)
{
	size_t		map_x;
	size_t		map_y;
	t_vec3x1	wall_position;

	map_y = 0;
	while (map_y < view->map.maxy)
	{
		map_x = 0;
		while (map_x < view->map.maxx)
		{
			if (view->map.tab[map_y][map_x].type == WALL)
			{
				wall_position.x = data->start_x + (map_x * data->minimap_width
						/ view->map.maxx);
				wall_position.y = data->start_y + (map_y * data->minimap_height
						/ view->map.maxy);
				wall_position.z = 0;
				drawsquare(wall_position, view, 0xFFFFFF, data->wall_size);
			}
			map_x++;
		}
		map_y++;
	}
}

void	draw_minimap_player(t_view *view, t_minimap_data *data,
	int squareproportion)
{
	int			player_mini_x;
	int			player_mini_y;
	t_vec3x1	player_position;

	player_mini_x = data->start_x + (view->player.x / squareproportion
			* data->minimap_width / view->map.maxx);
	player_mini_y = data->start_y + (view->player.y / squareproportion
			* data->minimap_height / view->map.maxy);
	player_position.x = player_mini_x;
	player_position.y = player_mini_y;
	player_position.z = 0;
	drawsquare(player_position, view, 0xFF0000, data->player_size);
}

void	draw_player_direction(t_view *view, t_minimap_data *data,
	int player_mini_x, int player_mini_y)
{
	float		direction_length;
	float		dir_x;
	float		dir_y;
	t_vec3x1	direction_start;
	t_vec3x1	direction_end;

	direction_length = data->player_size * 2;
	dir_x = cos(view->playerangle) * direction_length;
	dir_y = sin(view->playerangle) * direction_length;
	direction_start.x = player_mini_x + data->player_size * 0.5;
	direction_start.y = player_mini_y + data->player_size * 0.5;
	direction_end.x = player_mini_x + dir_x;
	direction_end.y = player_mini_y + dir_y;
	draw_line(&direction_start, &direction_end, view, 0xFFFF00);
}

void	draw_minimap(t_view *view, int squareproportion)
{
	t_minimap_data	data;
	int				player_mini_x;
	int				player_mini_y;

	init_minimap_data(&data, view);
	draw_minimap_background(view, &data);
	draw_minimap_walls(view, &data);
	draw_minimap_player(view, &data, squareproportion);
	player_mini_x = data.start_x + (view->player.x / squareproportion
			* data.minimap_width / view->map.maxx);
	player_mini_y = data.start_y + (view->player.y / squareproportion
			* data.minimap_height / view->map.maxy);
	draw_player_direction(view, &data, player_mini_x, player_mini_y);
}
