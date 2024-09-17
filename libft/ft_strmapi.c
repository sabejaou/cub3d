/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbejaoui <sbejaoui@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:24:31 by sbejaoui          #+#    #+#             */
/*   Updated: 2021/11/05 20:48:24 by sbejaoui         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	unsigned int	l;
	unsigned char	*a;

	i = 0;
	if (!s || !f)
		return (NULL);
	l = ft_strlen(s);
	a = (unsigned char *)ft_calloc(l + 1, sizeof(char));
	if (!a)
		return (NULL);
	while (i < l)
	{
		a[i] = f(i, s[i]);
		i++;
	}
	return ((char *)a);
}
