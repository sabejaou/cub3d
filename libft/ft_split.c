/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabejaou <sabejaou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 15:54:12 by sabejaou          #+#    #+#             */
/*   Updated: 2024/02/13 12:53:40 by sabejaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_c(char c, const char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (s && !s[0])
		return (1);
	while (s && s[i])
	{
		while (s && s[i] == c)
		{
			i++;
			if (s && s[i] != c)
				j++;
		}
		if (s && s[i])
			i++;
	}
	i--;
	if (s && s[0] == c && s[i] == c)
		return (j);
	if (s && (s[0] == c || s[i] == c))
		return (j + 1);
	return (j + 2);
}

int	ft_check_c(char c, char s)
{
	if (c == s)
		return (1);
	return (0);
}

char	*ft_strdupp(char const *s, char c, int *i)
{
	char	*str;
	int		size;
	int		j;

	str = 0;
	size = 0;
	j = 0;
	while (ft_check_c(s[*i], c) == 0 && s[*i])
	{
		size++;
		*i += 1;
	}
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (ft_calloc(1, 0));
	*i = *i - size;
	while (ft_check_c(s[*i], c) == 0 && s[*i])
	{
		str[j] = s[*i];
		*i += 1;
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**str;
	int		j;

	j = 0;
	str = 0;
	i = 0;
	if (!s)
		return (NULL);
	str = (char **)malloc(sizeof(char *) * ft_count_c(c, s));
	if (!str)
		return (NULL);
	while (s[i])
	{
		if (ft_check_c(c, s[i]) == 0)
		{
			str[j] = ft_strdupp(s, c, &i);
			j++;
		}
		else
			i++;
	}
	str[j] = 0;
	return (str);
}
