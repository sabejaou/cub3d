/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabejaou <sabejaou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:16:08 by sabejaou          #+#    #+#             */
/*   Updated: 2024/09/18 00:31:10 by sabejaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"
#include <unistd.h>

bool	ft_str_is_whitespace(char *str)
{
	size_t i;

	i = 0;
	if (!str)
		return (false);
	while (str[i])
	{
		if ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
			i++;
		else
			return (false);
	}
	return(true);
}

t_errcd ft_verify_textures(char *compass ,char *line, char **structtext)
{
	int i;

	i = 0;
	char **split;
	if (!ft_strncmp(compass, line, 3))
	{
		split = ft_split(line, ' ');
		if (!split)
			return (ERR_ALLOC);
		while (split[i])
			i++;
		if (i != 2)
			return (ERR_FORMAT_TEXTURE);
		else
		{
			*structtext = split[1];
			free(split[0]);
			free(split[2]);
			free(split);
			return (NO_ERROR);
		}
	}
	else
		return(ERR_ACCESS_TEXTURE);
}

t_errcd	ft_set_colors(char *line, t_vec3x1 *colors)
{
	int i;

	i = 0;
	char **split;
	split = ft_split(line, ',');
	if (!split)
		return (ERR_ALLOC);
	while (split[i])
		i++;
	if (i != 3)
		return (ERR_FORMAT_TEXTURE);
	else
	{
		colors->x = ft_atoi(split[0]);
		colors->y = ft_atoi(split[1]);
		colors->x = ft_atoi(split[2]);
	}
	free(split[0]);
	free(split[1]);
	free(split[2]);
	free(split[3]);
	free(split);
	free(line);
	return (NO_ERROR);
}

t_errcd	ft_verify_colors(char *compass, char *line, t_vec3x1 *colors)
{
	int i;

	i = 0;
	char **split;
	if (!ft_strncmp(compass, line, 2))
	{
		split = ft_split(line, ' ');
		if (!split)
			return (ERR_ALLOC);
		while (split[i])
			i++;
		if (i != 2)
			return (ERR_FORMAT_TEXTURE);
		else
		{
			ft_set_colors(split[1], &colors[i]);
			free(split[0]);
			free(split[2]);
			free(split);
			return (NO_ERROR);
		}
	}
	else
		return(ERR_ACCESS_TEXTURE);
}

t_errcd	ft_verify_map_colors(int *fd, t_view *view, char **line)
{
	int i;
	char compass[2][3] = {"F ", "C "};
	t_errcd err;

	err = NO_ERROR;
	i = 0;
	while (ft_str_is_whitespace(*line))
		*line = get_next_line(*fd, *line);
	while (line && i != 2)
	{
		err = ft_verify_colors(compass[i], *line, view->fccolor);
		if (err)
			return (err);
		*line = get_next_line(*fd, *line);
		if (!(*line))
			return (ERR_INVALID_MAP);
		i++;
	}
	return (err);
}

t_errcd ft_verify_map_textures(int *fd, char **line, t_view *view)
{
	int i;
	char compass[4][4] = {"NO ", "SO ", "WE ", "EA "};
	t_errcd err;

	err = NO_ERROR;
	i = 0;
	while (line && i < 4)
	{
		err = ft_verify_textures(compass[i], *line, &view->text[i]);
		if (err)
			return (err);
		*line = get_next_line(*fd, *line);
		if (!(*line))
			return (ERR_INVALID_MAP);
		i++;
	}
	err = ft_verify_map_colors(fd, view, line);
	return (err);
}

bool ft_is_map_char(char c)
{
	if (c == '1' || c == '0' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W' || c == ' ')
		return (true);
	return (false);
}

bool	ft_is_architecture_part(char *line)
{
	size_t i;

	i = 0;
	if (ft_str_is_whitespace(line))
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

t_errcd	ft_size_map_y(char *path, size_t *maxy, size_t *maxx)
{
	t_errcd err;
	char *line;
	int fd;

	*maxy = 0;
	*maxx = 0;
	fd = open(path, O_RDONLY);
	if (fd <= 2)
		return (ERR_ACCESS_MAP);
	err = NO_ERROR;
	line = NULL;
	line = get_next_line(fd, line);
	while (!ft_is_architecture_part(line))
		line = get_next_line(fd, line);
	if (!line)
		return (ERR_INVALID_MAP);
	*maxx = ft_strlen(line);
	while (ft_is_architecture_part(line))
	{
		(*maxy)++;
		line = get_next_line(fd, line);
		if (ft_strlen(line) > *maxx)
			*maxx = ft_strlen(line) - 1;
	}
	free(line);
	close(fd);
	return (err);
}

t_maptype ft_define_map_type(char c)
{
	if (c == '0')
		return (GROUND);
	else if (c == '1')
		return (WALL);
	else if (c == ' ' || c == '\n')
		return (VOID);
	else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (SPAWN);
	else
		return (INVALID);
}

void	ft_set_map_points(int *fd, char **line, t_view *view)
{
	size_t y;
	size_t x;

	y = 0;
	x = 0;
	while (!ft_is_architecture_part(*line))
		*line = get_next_line(*fd, *line);
	while ((*line) && y < view->map.maxy)
	{
		while (x < view->map.maxx)
		{
			if ((*line)[x])
			{
				view->map.tab[y][x].type = ft_define_map_type((*line)[x]);
				x++;
			}
			else if (!(*line)[x] && x < view->map.maxx)
				while (x < view->map.maxx)
				{
					view->map.tab[y][x].type = VOID;
					x++;
				}
		}
		*line = get_next_line(*fd, *line);
		y++;
		x = 0;
	}
}

t_errcd	ft_verify_map_architecture(int *fd, char **line, t_view *view, char *path)
{
	size_t y;
	t_errcd err;

	y = 0;
	close(*fd);
	err = ft_size_map_y(path, &(view->map.maxy), &(view->map.maxx));
	if (err)
		return (err);
	view->map.tab = malloc(sizeof(t_vec3x1 *) * view->map.maxy);
	if (!view->map.tab)
		return (ERR_ALLOC);
	while (y < view->map.maxy)
	{
		view->map.tab[y] = malloc(sizeof(t_vec3x1) * view->map.maxx);
		if (!view->map.tab[y])
		{
			// il faut free tous ceux d'avant
			return (ERR_ALLOC);
		}
		y++;
	}
	*fd = open(path, O_RDONLY);
	if (*fd <= 2)
		return (ERR_ACCESS_MAP);
	*line = get_next_line(*fd, *line);
	ft_set_map_points(fd, line, view);
	return (NO_ERROR);
}

t_errcd	ft_verify_map(int *fd, t_view *view, char *path)
{
	char	*line;
	t_errcd	err;

	err = NO_ERROR;
	line = NULL;
	line = get_next_line(*fd, line);
	while (ft_str_is_whitespace(line))
		line = get_next_line(*fd, line);
	err = ft_verify_map_textures(fd, &line, view);
	if (err)
		return (err);
	while (ft_str_is_whitespace(line))
		line = get_next_line(*fd, line);
	err = ft_verify_map_architecture(fd, &line, view, path);
	if (err)
		return (err);
	while (ft_str_is_whitespace(line))
		line = get_next_line(*fd, line);
	if (!*line)
	{
		// il faut free le view->map.tab
		return (ERR_FILE_CONSTRUCTION);
	}
	free(line);
	return (NO_ERROR);
}

t_errcd ft_parse_map(char *path, t_view *view)
{
	int fd;
	t_errcd	err;

	err = NO_ERROR;
	fd = open(path, O_RDONLY);
	if (fd <= 2)
		return (ERR_ACCESS_MAP);
	err = ft_verify_map(&fd, view, path);
	close(fd);
	return(err);
}

t_errcd ft_create_map(char *path, t_view *view)
{
	t_errcd		err;
	
	if (access(path, F_OK | R_OK) == -1)
		return (ERR_ACCESS_MAP);
	err = ft_parse_map(path, view);
	if (err != NO_ERROR)
		return (err);
	return (NO_ERROR);
}