/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawminimapinit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabejaou <sabejaou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 08:03:16 by sabejaou          #+#    #+#             */
/*   Updated: 2024/09/23 09:14:45 by sabejaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

#include "../../incl/cub3d.h"

void	init_minimap_data(t_minimap_data *data, t_view *view)
{
	data->minimap_width = 400;
	data->minimap_height = 400;
	data->start_x = 10;
	data->start_y = 10;
	data->wall_size = fmin(data->minimap_width / view->map.maxx,
			data->minimap_height / view->map.maxy);
	data->player_size = data->wall_size;
}

void	fill_background(t_view *view)
{
	int	ceiling_color;
	int	floor_color;
	int	y;
	int	x;
	int	color;

	ceiling_color = (view->ceil->r << 16)
		| (view->ceil->g << 8) | view->ceil->b;
	floor_color = (view->floor->r << 16)
		| (view->floor->g << 8) | view->floor->b;
	printf("%d\n", floor_color);
	printf("%d\n", ceiling_color);
	y = -1;
	while (++y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			color = floor_color;
			if (y < WINDOW_HEIGHT / 2)
				color = ceiling_color;
			((int *)view->addr)[y * (view->sl >> 2) + x] = color;
			x++;
		}
	}
}

void	draw_line(t_vec3x1 *start, t_vec3x1 *end, t_view *view, int col)
{
	t_drawlineutils	u;

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
	int			x;
	int			y;
	t_vec3x1	end;
	t_vec3x1	tmp;

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
