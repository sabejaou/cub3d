/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsofien- <tsofien-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 08:30:18 by sabejaou          #+#    #+#             */
/*   Updated: 2024/10/19 19:05:15 by tsofien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

t_errcd	ft_verify_map_textures(int *fd, char **line, t_view *view)
{
	int		i;
	t_errcd	err;

	err = NO_ERROR;
	i = -1;
	while (++i < 4)
	{
		err = ft_verify_textures(*line, &view->text[i]);
		if (err)
			return (free(*line), err);
		*line = get_next_line(*fd, *line, 0);
		while (ft_str_is_whitespace(*line))
			*line = get_next_line(*fd, *line, 0);
		if (!(*line))
			return (ERR_INVALID_MAP);
	}
	err = changetxtidx(&view->txtvrf, view);
	if (err)
		return (free(*line), err);
	err = ft_verify_map_colors(fd, view, line);
	while (ft_str_is_whitespace(*line))
		*line = get_next_line(*fd, *line, 0);
	if (!ft_is_architecture_part(*line))
		return (free(*line), err);
	return (err);
}

void	ft_set_map_points_helper(t_view *view, char *line, size_t *y, size_t *x)
{
	view->map.tab[*y][*x].x = *x;
	view->map.tab[*y][*x].y = *y;
	if (line[*x])
	{
		view->map.tab[*y][*x].type = ft_define_map_type(line[*x]);
		if (view->map.tab[*y][*x].type >= SPAWN_NORTH &&
			view->map.tab[*y][*x].type <= SPAWN_WEST)
		{
			view->player.x = *x;
			view->player.y = *y;
			view->player.z = view->map.tab[*y][*x].type;
			view->player.type = view->map.tab[*y][*x].type;
		}
		(*x)++;
	}
	else if (!line[*x] && *x < view->map.maxx)
	{
		while (*x < view->map.maxx)
		{
			view->map.tab[*y][*x].type = VOID;
			view->map.tab[*y][*x].x = *x;
			view->map.tab[*y][*x].y = *y;
			(*x)++;
		}
	}
}

t_errcd	ft_set_map_points(int *fd, char **line, t_view *view)
{
	size_t	y;
	size_t	x;

	y = 0;
	x = 0;
	while (!ft_is_architecture_part(*line))
		*line = get_next_line(*fd, *line, 0);
	while ((*line) && y < view->map.maxy)
	{
		while (x < view->map.maxx)
			ft_set_map_points_helper(view, *line, &y, &x);
		if (y < view->map.maxy)
			*line = get_next_line(*fd, *line, 0);
		y++;
		x = 0;
	}
	return (NO_ERROR);
}

t_errcd	ft_verify_map_architecture(int *fd, char **line, t_view *view,
	char *path)
{
	size_t	y;
	t_errcd	err;

	y = 0;
	close(*fd);
	err = ft_size_map_y(path, &(view->map.maxy), &(view->map.maxx));
	if (view->map.maxy < 3 || view->map.maxx < 3)
		return (free(*line), ERR_INVALID_MAP);
	view->map.tab = ft_calloc(view->map.maxy, sizeof(t_vec3x1 *));
	if (!view->map.tab)
		return (ERR_ALLOC);
	while (y < view->map.maxy)
	{
		allocate_taby(view, y);
		if (!view->map.tab[y++])
			return (ft_free_map_partial(view, y), ERR_ALLOC);
	}
	*fd = open(path, O_RDONLY);
	if (*fd <= 2)
		return (ERR_ACCESS_MAP);
	get_next_line(0, NULL, 1);
	*line = get_next_line(*fd, *line, 0);
	err = ft_set_map_points(fd, line, view);
	return (NO_ERROR);
}

t_errcd	ft_verify_map(int *fd, t_view *view, char *path)
{
	char	*line;
	t_errcd	err;

	err = NO_ERROR;
	line = NULL;
	line = get_next_line(*fd, line, 0);
	while (ft_str_is_whitespace(line))
		line = get_next_line(*fd, line, 0);
	err = ft_verify_map_textures(fd, &line, view);
	if (err)
		return (err);
	while (ft_str_is_whitespace(line))
		line = get_next_line(*fd, line, 0);
	err = ft_verify_map_architecture(fd, &line, view, path);
	if (err)
		return (err);
	while (ft_str_is_whitespace(line))
		line = get_next_line(*fd, line, 0);
	if (line)
	{
		free(line);
		return (ERR_FILE_CONSTRUCTION);
	}
	free(line);
	return (NO_ERROR);
}
