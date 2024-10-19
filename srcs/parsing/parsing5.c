/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsofien- <tsofien-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 18:59:28 by tsofien-          #+#    #+#             */
/*   Updated: 2024/10/19 20:07:56 by tsofien-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void	replacewhitespace(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] > 8 && str[i] < 14)
			str[i] = ' ';
		i++;
	}
}

bool	colorisvalid(char *str)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(str))
	{
		if (!ft_isdigit(str[i]) && str[i] != ',')
			return (0);
		i++;
	}
	return (1);
}

char	*splittxt(char *txt)
{
	int	i;

	i = 2;
	while (txt[i] == ' ')
		i++;
	return (ft_substr(txt, i, ft_strlen(txt)));
}

void	compall(char *txt, char *cardinal[4], char ***tmp, t_cardinal *vrf)
{
	if (!ft_strncmp(cardinal[0], txt, 3) && !vrf->no)
	{
		(*tmp)[0] = splittxt(txt);
		vrf->no = 1;
	}
	else if (!ft_strncmp(cardinal[1], txt, 3) && !vrf->so)
	{
		(*tmp)[1] = splittxt(txt);
		vrf->so = 1;
	}
	else if (!ft_strncmp(cardinal[2], txt, 3) && !vrf->we)
	{
		(*tmp)[2] = splittxt(txt);
		vrf->we = 1;
	}
	else if (!ft_strncmp(cardinal[3], txt, 3) && !vrf->ea)
	{
		(*tmp)[3] = splittxt(txt);
		vrf->ea = 1;
	}
}

t_errcd	changetxtidx(t_cardinal *vrf, t_view *view)
{
	int		i;
	char	**tmp;
	char	*cardinal[4];

	i = 0;
	cardinal[0] = "NO ";
	cardinal[1] = "SO ";
	cardinal[2] = "WE ";
	cardinal[3] = "EA ";
	tmp = ft_calloc(4, sizeof(char *));
	while (i < 4)
		compall(view->text[i++], cardinal, &tmp, vrf);
	free(view->text[0]);
	free(view->text[1]);
	free(view->text[2]);
	free(view->text[3]);
	i = -1;
	while (++i < 4)
		view->text[i] = tmp[i];
	free(tmp);
	if (!view->txtvrf.ea || !view->txtvrf.we || !view->txtvrf.so
		|| !view->txtvrf.no)
		return (ERR_FORMAT_TEXTURE);
	return (NO_ERROR);
}
