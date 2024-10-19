/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsofien- <tsofien-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 08:32:03 by sabejaou          #+#    #+#             */
/*   Updated: 2024/10/19 19:26:16 by tsofien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

void	allocate_taby(t_view *view, size_t y)
{
	if (view->map.maxx >= view->map.maxy)
		view->map.tab[y] = ft_calloc(view->map.maxx, sizeof(t_vec3x1));
	else
		view->map.tab[y] = ft_calloc(view->map.maxy, sizeof(t_vec3x1));
}

void	ft_free_map_partial(t_view *view, size_t y)
{
	size_t	i;

	i = 0;
	while (i < y)
	{
		if (view->map.tab[i])
			free(view->map.tab[i]);
		i++;
	}
	if (view->map.tab)
		free(view->map.tab);
	view->map.tab = NULL;
}

t_errcd	ft_verify_map_colors(int *fd, t_view *view, char **line)
{
	t_vmapcols	a;

	init_vmapcols(&a, fd, line);
	while (line && a.i != 2 && a.i != -1)
	{
		a.err = ft_verify_colors(a.compass[a.i], line, view, a.i);
		if (a.err)
			return (a.err);
		*line = get_next_line(*fd, *line, 0);
		while (ft_str_is_whitespace(*line))
			*line = get_next_line(*fd, *line, 0);
		if (!(*line))
			return (ERR_INVALID_MAP);
		if (a.sense)
			a.i--;
		else
			a.i++;
	}
	while (ft_str_is_whitespace(*line))
		*line = get_next_line(*fd, *line, 0);
	if (!ft_is_architecture_part(*line))
		return (ERR_INVALID_MAP);
	return (a.err);
}

bool	ft_is_map_char(char c)
{
	if (c == '1' || c == '0' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W' || c == ' ')
		return (true);
	return (false);
}

bool	ft_is_architecture_part(char *line)
{
	size_t	i;

	i = 0;
	if (!line || ft_str_is_whitespace(line))
		return (false);
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\n' || ft_is_map_char(line[i]))
			i++;
		else
			return (false);
	}
	return (true);
}
