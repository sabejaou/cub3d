/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabejaou <sabejaou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:16:08 by sabejaou          #+#    #+#             */
/*   Updated: 2024/09/23 08:52:49 by sabejaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

#include "../../incl/cub3d.h"

static t_errcd	ft_init_map_size(char *path, int *fd, char **line)
{
	*fd = open(path, O_RDONLY);
	get_next_line(0, NULL, 1);
	if (*fd <= 2)
		return (ERR_ACCESS_MAP);
	*line = NULL;
	*line = get_next_line(*fd, *line, 0);
	while (*line && !ft_is_architecture_part(*line))
		*line = get_next_line(*fd, *line, 0);
	if (!*line)
		return (ERR_INVALID_MAP);
	return (NO_ERROR);
}

t_errcd	ft_size_map_y(char *path, size_t *maxy, size_t *maxx)
{
	t_errcd	err;
	char	*line;
	int		fd;

	*maxy = 0;
	*maxx = 0;
	err = ft_init_map_size(path, &fd, &line);
	if (err != NO_ERROR)
		return (err);
	*maxx = ft_strlen(line) - 1;
	while (ft_is_architecture_part(line))
	{
		(*maxy)++;
		line = get_next_line(fd, line, 0);
		if (ft_strlen(line) > *maxx && ft_is_architecture_part(line))
		{
			if (ft_gnlstrchr(line, '\n') >= 0)
				*maxx = ft_strlen(line) - 1;
			else
				*maxx = ft_strlen(line);
		}
	}
	free(line);
	close(fd);
	return (NO_ERROR);
}

t_maptype	ft_define_map_type(char c)
{
	if (c == '0')
		return (GROUND);
	else if (c == '1')
		return (WALL);
	else if (c == ' ' || c == '\n')
		return (VOID);
	else if (c == 'N')
		return (SPAWN_NORTH);
	else if (c == 'W')
		return (SPAWN_WEST);
	else if (c == 'E')
		return (SPAWN_EAST);
	else if (c == 'S')
		return (SPAWN_SOUTH);
	else
		return (INVALID);
}

t_errcd	ft_parse_map(char *path, t_view *view)
{
	int		fd;
	t_errcd	err;

	err = NO_ERROR;
	fd = open(path, O_RDONLY);
	if (fd <= 2)
		return (ERR_ACCESS_MAP);
	err = ft_verify_map(&fd, view, path);
	close(fd);
	return (err);
}

t_errcd	ft_create_map(char *path, t_view *view)
{
	t_errcd	err;
	int		i;
	char	*endl;

	if (access(path, F_OK | R_OK) == -1)
		return (ERR_ACCESS_MAP);
	if (!ft_good_extension(ft_substr(path, ft_strlen(path) - 4, 4), ".cub", 5))
		return (ERR_EXTENSION_MAP);
	err = ft_parse_map(path, view);
	if (err != NO_ERROR)
		return (err);
	i = 0;
	while (i <= 3)
	{
		endl = ft_strchr(view->text[i], '\n');
		if (endl)
			*endl = '\0';
		if (access(view->text[i++], F_OK | R_OK) == -1)
			return (ERR_ACCESS_TEXTURE);
	}
	return (NO_ERROR);
}
