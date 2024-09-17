/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabejaou <sabejaou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 03:33:33 by sbejaoui          #+#    #+#             */
/*   Updated: 2024/09/17 19:16:34 by sabejaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>
# include <math.h>
# include <stdbool.h>
# include "../libmlx/mlx.h"
# include "../libft/libft.h"
# include "errors_cub3d.h"
# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080
# define LEFT_ARROW_KEY 65430
# define RIGHT_ARROW_KEY 65432
# define UP_ARROW_KEY 65437
# define DOWN_ARROW_KEY 65433

typedef struct s_vec3x1
{
	double	x;
	double	y;
	double	z;
}	t_vec3x1;

typedef struct s_tab3x1
{
	t_vec3x1	*tab;
	size_t		max_size;
	size_t		maxx;
	size_t		maxy;
}	t_tab3x1;

typedef struct s_view
{
	t_vec3x1	**map;
	char		*text[4];
	t_vec3x1	fccolor[2];
	int			bpp;
	int			sl;
	int			endian;
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img;
	char		*addr;
}	t_view;

// Parsing
t_errcd ft_create_map(char *path, t_view *view);
#endif