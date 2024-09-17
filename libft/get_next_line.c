/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabejaou <sabejaou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 13:41:44 by sbejaoui          #+#    #+#             */
/*   Updated: 2024/09/18 00:17:32 by sabejaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_gnlstrcat(char *dest, char *src, int size)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (dest[i] != '\0')
		i++;
	while ((src[j] != '\0' && size == -1) || j <= size)
		dest[i++] = src[j++];
	dest[i] = '\0';
	while (src[j])
		src[k++] = src[j++];
	while (src[k])
		src[k++] = 0;
	dest[i] = '\0';
	return (dest);
}

int	ft_gnlbeginning(char **line, char *buffer, int fd, int *i)
{
	size_t	okou;

	okou = 0;
	if (!buffer[0])
	{
		*i = read(fd, buffer, BUFFER_SIZE);
		if (*i < 0)
		{
			ft_gnlbzero(buffer, BUFFER_SIZE);
			return (-1);
		}
		buffer[BUFFER_SIZE] = '\0';
	}
	else
	{
		okou = ft_gnlstrlen(buffer);
		if (ft_gnlstrchr(buffer, '\n') != -1)
			okou = ft_gnlstrchr(buffer, '\n');
		*line = ft_gnlstrealloc(*line, okou);
		if (!(*line))
			return (-1);
		ft_gnlstrcat(*line, buffer, okou);
	}
	return (0);
}

void	*ft_gnlend(char **line, char *buffer, int *i)
{
	int	okou;

	okou = 0;
	okou = ft_gnlstrchr(buffer, '\n');
	if (i == 0)
		okou = ft_gnlstrchr(buffer, '\0');
	*line = ft_gnlstrealloc(*line, okou);
	if (!(*line))
		return (NULL);
	ft_gnlstrcat(*line, buffer, okou);
	return (*line);
}

char	*get_next_line(int fd, char *oldline)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	int			i;

	i = 1;
	line = NULL;
	if (oldline)
		free(oldline);
	while (i && fd >= 0 && BUFFER_SIZE >= 1 && fd < OPEN_MAX && !read(fd, 0, 0))
	{
		if ((ft_gnlbeginning(&line, buffer, fd, &i)) == -1)
			return (NULL);
		if (ft_gnlstrchr(line, '\n') != -1)
			return (line);
		if (ft_gnlstrchr(buffer, '\n') == -1 && buffer[0])
		{
			line = ft_gnlstrealloc(line, BUFFER_SIZE);
			if (!line)
				return (NULL);
			ft_gnlstrcat(line, buffer, -1);
		}
		if (!buffer[0] && i == 0)
			return (line);
		else if (buffer[0] || i == 0)
			return (ft_gnlend(&line, buffer, &i));
	}
	return (NULL);
}
