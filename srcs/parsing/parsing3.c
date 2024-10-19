/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsofien- <tsofien-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 08:31:10 by sabejaou          #+#    #+#             */
/*   Updated: 2024/10/19 20:07:44 by tsofien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

bool	ft_str_is_whitespace(char *str)
{
	size_t	i;

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
	return (true);
}

bool	ft_good_extension(char *ext, char *ext_expected, int len)
{
	if (!*ext || !ft_strncmp(ext_expected, ext, len))
	{
		if (ext)
			free(ext);
		return (1);
	}
	if (ext)
		free(ext);
	return (0);
}

t_errcd	ft_verify_textures(char *line, char **structtext)
{
	int		i;
	int		j;
	char	**split;

	i = 0;
	j = -1;
	if (!line)
		return (ERR_INVALID_MAP);
	while (line[++j])
		if (line[j] > 8 && line[j] < 14)
			line[j] = ' ';
	split = ft_split(line, ' ');
	if (!split)
		return (ERR_ALLOC);
	while (split[i])
		i++;
	if (!ft_good_extension(ft_substr(split[i],
				ft_strlen(split[i]) - 5, 5), ".xpm\n", 6))
		return (free(line), ft_free_tab(split), ERR_FORMAT_TEXTURE);
	*structtext = ft_substr(line, 0, ft_strlen(line) - 1);
	ft_free_tab(split);
	return (NO_ERROR);
}

t_errcd	ft_set_colors(char *line, t_view *view, int j)
{
	int		i;
	char	**split;

	i = 0;
	if (!colorisvalid(line))
		return (free(line), ERR_COLOR_FORMAT);
	split = ft_split(line, ',');
	free(line);
	line = NULL;
	if (!split)
		return (ERR_ALLOC);
	while (split[i])
		i++;
	if (i != 3)
		return (ft_free_tab(split), ERR_COLOR_FORMAT);
	(view)->fccolor[j].r = abs(ft_atoi(split[0])) % 256;
	(view)->fccolor[j].g = abs(ft_atoi(split[1])) % 256;
	(view)->fccolor[j].b = abs(ft_atoi(split[2])) % 256;
	if (j == 1)
		view->ceil = &(view)->fccolor[j];
	else
		view->floor = &(view)->fccolor[j];
	ft_free_tab(split);
	return (NO_ERROR);
}

t_errcd	ft_verify_colors(char *compass, char **line, t_view *view, int j)
{
	int		i;
	char	**split;
	t_errcd	err;

	i = 0;
	err = NO_ERROR;
	if (!ft_strncmp(compass, *line, 2))
	{
		replacewhitespace(*line);
		split = ft_split(*line, ' ');
		free(*line);
		*line = NULL;
		if (!split)
			return (ERR_ALLOC);
		while (split[i])
			i++;
		if (i != 2)
			return (ft_free_tab(split), ERR_COLOR_FORMAT);
		err = ft_set_colors(ft_strdup(split[1]), view, j);
		return (ft_free_tab(split), err);
	}
	free(*line);
	*line = NULL;
	return (ERR_ACCESS_TEXTURE);
}
