/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabejaou <sabejaou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 15:55:31 by sabejaou          #+#    #+#             */
/*   Updated: 2023/11/04 15:55:32 by sabejaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sstr;
	int		i;

	i = 0;
	if (len <= 0 || !s || start >= ft_strlen(s))
		return (ft_strdup(""));
	s = &s[start];
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	sstr = (char *)malloc((len + 1) * sizeof(char));
	if (!sstr)
		return (NULL);
	while (len > 0 && s[i])
	{
		sstr[i] = s[i];
		i++;
		len--;
	}
	sstr[i] = '\0';
	return (sstr);
}
