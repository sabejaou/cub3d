/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabejaou <sabejaou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 03:33:33 by sbejaoui          #+#    #+#             */
/*   Updated: 2024/09/17 11:51:57 by sabejaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>
# include <math.h>
# include "../libmlx/mlx.h"
# include "../libft/libft.h"
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
	t_tab3x1	*map;
	double		zoom;
	int			bpp;
	int			sl;
	int			endian;
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img;
	char		*addr;
}	t_view;

typedef struct s_line
{
	double	dx;
	double	dy;
	double	steps;
	double	x_inc;
	double	y_inc;
}	t_line;

typedef struct s_draw_data
{
	size_t		x;
	size_t		y;
	size_t		next_x;
	size_t		next_y;
	t_vec3x1	start;
	t_vec3x1	end;
}	t_draw_data;

typedef struct s_utils
{
	int		fd;
	char	*line;
	char	**values;
	size_t	y;
	size_t	x_count;
}	t_utils;

typedef struct s_drawlineutils
{
	double	dx;
	double	dy;
	double	steps;
	double	y_inc;
	double	x_inc;
	double	y;
	double	x;
	int		i;
}	t_drawlineutils;

#endif