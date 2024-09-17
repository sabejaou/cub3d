/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabejaou <sabejaou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 15:55:20 by sabejaou          #+#    #+#             */
/*   Updated: 2023/11/04 15:55:20 by sabejaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int to_find)
{
	int	i;

	to_find = (unsigned char)to_find;
	i = ft_strlen(str);
	while (i >= 0)
	{
		if (str[i] == to_find)
			return ((char *)&str[i]);
		i--;
	}
	return (0);
}
