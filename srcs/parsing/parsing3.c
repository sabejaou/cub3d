/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabejaou <sabejaou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 08:31:10 by sabejaou          #+#    #+#             */
/*   Updated: 2024/10/07 17:14:31 by sabejaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"
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

t_errcd	ft_verify_textures(char *compass, char *line, char **structtext)
{
	int		i;
	char	**split;

	i = 0;
	if (!line)
		return(ERR_INVALID_MAP);
	if (!ft_strncmp(compass, line, 3))
	{
		split = ft_split(line, ' ');
		if (!split)
			return (ERR_ALLOC);
		while (split[i])
			i++;
		if (i != 2 || !ft_good_extension(ft_substr(split[1],
					ft_strlen(split[1]) - 5, 5), ".xpm\n", 6))
			return (ERR_FORMAT_TEXTURE);
		*structtext = split[1];
		free(split[0]);
		free(split[2]);
		free(split);
		return (NO_ERROR);
	}
	return (ERR_ACCESS_TEXTURE);
}

t_errcd	ft_set_colors(char *line, t_view *view, int j)
{
	int		i;
	char	**split;

	i = 0;
	split = ft_split(line, ',');
	if (!split)
		return (ERR_ALLOC);
	while (split[i])
		i++;
	if (i != 3)
		return (ERR_COLOR_FORMAT);
	(view)->fccolor[j].r = ft_atoi(split[0]);
	(view)->fccolor[j].g = ft_atoi(split[1]);
	(view)->fccolor[j].b = ft_atoi(split[2]);
	if (j == 1)
		view->ceil = &(view)->fccolor[j];
	else
		view->floor = &(view)->fccolor[j];
	free(split[0]);
	free(split[1]);
	free(split[2]);
	free(split[3]);
	free(split);
	free(line);
	return (NO_ERROR);
}

t_errcd	ft_verify_colors(char *compass, char *line, t_view *view, int j)
{
	int		i;
	char	**split;

	i = 0;
	if (!ft_strncmp(compass, line, 2))
	{
		split = ft_split(line, ' ');
		if (!split)
			return (ERR_ALLOC);
		while (split[i])
			i++;
		if (i != 2)
			return (ERR_COLOR_FORMAT);
		ft_set_colors(split[1], view, j);
		free(split[0]);
		free(split[2]);
		free(split);
		return (NO_ERROR);
	}
	return (ERR_ACCESS_TEXTURE);
}
