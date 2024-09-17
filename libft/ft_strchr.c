/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabejaou <sabejaou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 15:54:19 by sabejaou          #+#    #+#             */
/*   Updated: 2023/11/04 15:54:19 by sabejaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int to_find)
{
	int	i;

	i = 0;
	to_find = (unsigned char)to_find;
	while (str[i])
	{
		if (str[i] == to_find)
			return ((char *)str + i);
		i++;
	}
	if (str[i] == to_find)
		return ((char *)str + i);
	return (0);
}
