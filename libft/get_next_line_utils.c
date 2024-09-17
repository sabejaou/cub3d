/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabejaou <sabejaou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 13:41:40 by sbejaoui          #+#    #+#             */
/*   Updated: 2024/01/18 04:21:14 by sabejaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_gnlbzero(void *s, size_t n)
{
	unsigned char	*z;
	size_t			i;

	z = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		z[i] = 0;
		i++;
	}
}

size_t	ft_gnlstrlen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

void	*ft_gnlcalloc(size_t nmemb, size_t size)
{
	unsigned char	*tab;
	unsigned char	*z;
	size_t			i;

	i = 0;
	tab = (unsigned char *)malloc(nmemb * size);
	if (!tab)
		return (NULL);
	z = tab;
	while (i < nmemb * size)
	{
		z[i] = 0;
		i++;
	}
	return (tab);
}

char	*ft_gnlstrealloc(char *src, int n)
{
	size_t	i;
	size_t	j;
	char	*dst;

	i = 0;
	dst = NULL;
	j = ft_gnlstrlen(src);
	dst = ft_gnlcalloc((j + n + 2), sizeof(char));
	if (dst)
	{
		if (!src)
		{
			return (dst);
		}
		while (i < j + n && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[j + n] = '\0';
		if (src)
			free(src);
		return (dst);
	}
	return (0);
}

int	ft_gnlstrchr(char *str, char to_find)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == to_find)
			return (i);
		i++;
	}
	if (str[i] == to_find)
		return (i);
	return (-1);
}
