/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsofien- <tsofien-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:32:55 by tsofien-          #+#    #+#             */
/*   Updated: 2024/10/10 18:43:37 by tsofien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	while (--i >= 0)
		free(tab[i]);
	free(tab);
}
