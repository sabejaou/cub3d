/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabejaou <sabejaou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 08:32:03 by sabejaou          #+#    #+#             */
/*   Updated: 2024/09/23 08:59:26 by sabejaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/cub3d.h"

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
	int		i;
	char	compass[2][3];
	t_errcd	err;

	err = NO_ERROR;
	i = 0;
	ft_strlcpy(compass[0], "F ", 3);
	ft_strlcpy(compass[1], "C ", 3);
	while (ft_str_is_whitespace(*line))
		*line = get_next_line(*fd, *line, 0);
	while (line && i != 2)
	{
		err = ft_verify_colors(compass[i], *line, view, i);
		if (err)
			return (err);
		*line = get_next_line(*fd, *line, 0);
		if (!(*line))
			return (ERR_INVALID_MAP);
		i++;
	}
	return (err);
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
