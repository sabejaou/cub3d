/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapscan.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabejaou <sabejaou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:52:00 by sabejaou          #+#    #+#             */
/*   Updated: 2024/10/07 16:59:02 by sabejaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

t_errcd	ft_is_valid(t_tab3x1 map, size_t y, size_t x)
{
	if (y == 0 || y == map.maxy - 1 || x == 0 || x == map.maxx - 1)
		return (ERR_INVALID_MAP);
	if (map.tab[y - 1][x].type > WALL || map.tab[y + 1][x].type > WALL)
		return (ERR_INVALID_MAP);
	if (map.tab[y][x - 1].type > WALL || map.tab[y][x + 1].type > WALL)
		return (ERR_INVALID_MAP);
	return (NO_ERROR);
}

t_errcd	ft_is_valid_next(t_vec3x1 v, t_tab3x1 *map, size_t y, size_t x)
{
	if (v.type == INVALID)
		return (ERR_INVALID_MAP);
	else if (v.type == GROUND)
	{
		map->is_ground = 1;
		return (ft_is_valid(*map, y, x));
	}
	else if (v.type >= SPAWN_NORTH && v.type <= SPAWN_WEST)
	{
		(map->player_count)++;
		return (ft_is_valid(*map, y, x));
	}
	return (NO_ERROR);
}

t_errcd	ft_scanmap(t_tab3x1 map)
{
	size_t	y;
	size_t	x;
	t_errcd	err;

	y = 0;
	err = NO_ERROR;
	map.is_ground = 0;
	map.player_count = 0;
	while (y < map.maxy)
	{
		x = 0;
		while (x < map.maxx)
		{
			err = ft_is_valid_next(map.tab[y][x], &map, y, x);
			if (err != NO_ERROR)
				return (err);
			x++;
		}
		y++;
	}
	if (map.player_count != 1)
		return (ERR_INVALID_MAP);
	if (!map.is_ground)
		return (ERR_INVALID_MAP);
	return (NO_ERROR);
}
