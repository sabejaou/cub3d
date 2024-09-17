/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabejaou <sabejaou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:27:01 by sabejaou          #+#    #+#             */
/*   Updated: 2023/11/03 17:27:03 by sabejaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_putnbr(long long int n, char *a, int i)
{
	if (n >= 10)
	{
		i--;
		ft_putnbr(n / 10, a, i);
		a[i] = ((n % 10) + '0');
	}
	else if (n < 10 && n >= 0)
	{
		i--;
		a[i] = (n + '0');
	}
	return (a);
}

int	ft_count(long long int i)
{
	int	j;

	j = 2;
	if (i < 0)
	{
		j++;
		i *= -1;
	}
	while (i > 10)
	{
		i /= 10;
		j++;
	}
	if (i == 10)
	{
		j++;
	}
	return (j);
}

void	*ft_part(int n)
{
	char	*a;
	int		i;

	i = 0;
	if (n == -10)
	{
		a = (char *)malloc(4);
		a[i++] = '-';
		a[i++] = '1';
		a[i++] = '0';
		a[i] = '\0';
	}
	if (n == 10)
	{
		a = (char *)malloc(3);
		a[i++] = '1';
		a[i++] = '0';
		a[i] = '\0';
	}
	return (a);
}

char	*ft_itoa(int n)
{
	long long int		i;
	char				*a;

	i = n;
	n = ft_count(i);
	if (i == -10 || i == 10)
		return (ft_part(i));
	a = (char *)malloc(sizeof(char) * n);
	if (!a)
		return (NULL);
	a[n - 1] = 0;
	if (i < 0)
	{
		a[0] = '-';
		i *= -1;
	}
	return (ft_putnbr(i, a, n - 1));
}
