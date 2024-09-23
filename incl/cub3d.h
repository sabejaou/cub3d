/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabejaou <sabejaou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 03:33:33 by sbejaoui          #+#    #+#             */
/*   Updated: 2024/09/23 07:51:06 by sabejaou         ###   ########.fr       */
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
# define ROTATE_SPEED M_PI/30
# define LEFT_ARROW_KEY 65430
# define RIGHT_ARROW_KEY 65432
# define UP_ARROW_KEY 65437
# define DOWN_ARROW_KEY 65433
# define ESC_KEY 65307
# define W_ARROW_KEY    65362
# define S_ARROW_KEY  65364
# define A_ARROW_KEY 65361
# define D_ARROW_KEY 65363
# define W_KEY    119
# define S_KEY  115
# define A_KEY 97
# define D_KEY 100

typedef enum e_maptype
{
	GROUND = 0,
	SPAWN_NORTH   = 1,
	SPAWN_SOUTH   = 2,
	SPAWN_EAST   = 3,
	SPAWN_WEST   = 4,
	WALL   = 5,
	VOID = 6,
	INVALID = 7,
} t_maptype;

typedef struct s_vec3x1
{
	t_maptype type;
	double	x;
	double	y;
	double	z;
}	t_vec3x1;

typedef struct s_cols
{
	int	r;
	int	g;
	int	b;
}	t_cols;

typedef struct {
    float x;
	float y;
} Vector2f;

typedef struct s_ray_data {
	Vector2f ray_dir;
	Vector2f step_size;
	Vector2f map_check;
	Vector2f ray_length_1d;
	Vector2f step;
	float distance;
	int hit_vertical;
	int texture_index;
} t_ray_data;

typedef struct {
    float distance;
    int texture_index;
    float wall_x;
    int map_x;
    int map_y;
} RaycastHit;

typedef struct s_minimap_data {
	int minimap_width;
	int minimap_height;
	int start_x;
	int start_y;
	int wall_size;
	int player_size;
} t_minimap_data;

typedef struct s_tab3x1
{
	t_vec3x1	**tab;
	size_t		max_size;
	size_t		maxx;
	size_t		maxy;
	size_t 		player_count;
	bool		is_ground;
}	t_tab3x1;

typedef struct s_view
{
	t_tab3x1	map;
   void *textures[4];
    char *text[4];
    int texture_width[4];
    int texture_height[4];
	t_cols	fccolor[2];
	t_cols	*ceil;
	t_cols	*floor;
	t_vec3x1	player;
	float		playerangle;
	int			bpp;
	int			sl;
	int			endian;
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img;
	char		*addr;
}	t_view;

typedef struct s_drawmaputils
{
	size_t		x;
	size_t		y;
	size_t		next_x;
	size_t		next_y;
	t_vec3x1	start;
	t_vec3x1	end;
}	t_drawmaputils;

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

// Parsing
t_errcd ft_create_map(char *path, t_view *view);
t_errcd ft_scanmap(t_tab3x1 map);
#endif