/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabejaou <sabejaou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 12:16:08 by sabejaou          #+#    #+#             */
/*   Updated: 2024/09/17 19:37:38 by sabejaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	ft_str_is_whitespace(char *str)
{
	size_t i;

	i = 0;
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
		return (NO_ERROR);
	}
	free(split[0]);
	free(split[1]);
	free(split[2]);
	free(split[3]);
	free(split);
	free(line);
}

t_errcd	ft_verify_colors(char *compass, char *line, t_vec3x1 *colors)
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
			ft_set_colors(split[1], &(*colors)[i]);
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
		*line = get_next_line(*fd);
	while (line && i != 2)
	{
		err = ft_verify_colors(compass[i], *line, view->fccolor);
		if (err)
			return (err);
		*line = get_next_line(*fd);
		if (ft_str_is_whitespace(*line) || !*line)
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
	while (line && i != 4)
	{
		err = ft_verify_textures(compass[i], *line, &view->text[i]);
		if (err)
			return (err);
		*line = get_next_line(*fd);
		if (ft_str_is_whitespace(*line) || !*line)
			return (ERR_INVALID_MAP);
		i++;
	}
	err = ft_verify_map_colors();
	
}

bool	ft_is_architecture_part()
{
	
}

t_errcd	ft_verify_map_architecture(int *fd, char **line, t_view *view)
{
	t_vec3x1 **map;
}

t_errcd	ft_verify_map(int *fd, t_view *view)
{
	char	*line;
	t_errcd	err;

	err = NO_ERROR;
	line = get_next_line(*fd);
	while (ft_str_is_whitespace(line))
		line = get_next_line(*fd);
	err = ft_verify_map_textures(fd, &line, view);
	if (err)
		return (err);
	while (ft_str_is_whitespace(line))
		line = get_next_line(*fd);
	err = ft_verify_map_architecture(fd, &line, view);
	if (err)
		return (err);
	while (ft_str_is_whitespace(line))
		line = get_next_line(*fd);
	if (line)
		return (ERR_FILE_CONSTRUCTION);
	return (NO_ERROR);
}

t_errcd ft_parse_map(char *path, t_view *view)
{
	int fd;
	char *line;

	fd = open(path, O_RDONLY);
	if (fd <= 2)
		return (ERR_ACCESS_MAP);
	ft_verify_map(&fd, view);
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