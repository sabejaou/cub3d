/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsofien- <tsofien-@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 03:33:33 by sbejaoui          #+#    #+#             */
/*   Updated: 2024/10/19 20:09:07 by tsofien-         ###   ########.fr       */
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
# define WINDOW_WIDTH 1080
# define WINDOW_HEIGHT 720
# define ROTATE_SPEED 0.10471975512
# define LEFT_ARROW_KEY 65430
# define RIGHT_ARROW_KEY 65432
# define UP_ARROW_KEY 65437
# define DOWN_ARROW_KEY 65433
# define ESC_KEY 65307
# define W_ARROW_KEY 65362
# define S_ARROW_KEY 65364
# define A_ARROW_KEY 65361
# define D_ARROW_KEY 65363
# define W_KEY 119
# define S_KEY 115
# define A_KEY 97
# define D_KEY 100

typedef enum e_maptype
{
	GROUND = 0,
	SPAWN_NORTH = 1,
	SPAWN_SOUTH = 2,
	SPAWN_EAST = 3,
	SPAWN_WEST = 4,
	WALL = 5,
	VOID = 6,
	INVALID = 7,
}	t_maptype;

typedef enum e_cardinalenum
{
	INVALIDCRD = 0,
	NORTH = 1,
	SOUTH = 2,
	EAST = 3,
	WEST = 4,
}	t_cardinalenum;

typedef struct s_vec3x1
{
	t_maptype	type;
	double		x;
	double		y;
	double		z;
}	t_vec3x1;

typedef struct s_cols
{
	int	r;
	int	g;
	int	b;
}	t_cols;

typedef struct s_vector2f
{
	float	x;
	float	y;
}	t_vector2f;

typedef struct s_ray_data
{
	t_vector2f	ray_dir;
	t_vector2f	step_size;
	t_vector2f	map_check;
	t_vector2f	ray_length_1d;
	t_vector2f	step;
	float		distance;
	int			hit_vertical;
	int			texture_index;
}	t_ray_data;

typedef struct s_draw_data
{
	t_vector2f	player_pos;
	float		fov;
	float		ray_step;
	int			squareproportion;
}	t_draw_data;

typedef struct s_ray_result
{
	float	perp_distance;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_x;
	double	step;
	double	tex_pos;
}	t_ray_result;

typedef struct s_move_data
{
	float	new_x;
	float	new_y;
	float	move_speed;
	float	hitbox_radius;
	int		squareproportion;
}	t_move_data;

typedef struct s_raycast_hit
{
	float	distance;
	int		texture_index;
	float	wall_x;
	int		map_x;
	int		map_y;
}	t_raycast_hit;

typedef struct s_minimap_data
{
	int	minimap_width;
	int	minimap_height;
	int	start_x;
	int	start_y;
	int	wall_size;
	int	player_size;
}	t_minimap_data;

typedef struct s_tab3x1
{
	t_vec3x1	**tab;
	size_t		max_size;
	size_t		maxx;
	size_t		maxy;
	size_t		player_count;
	bool		is_ground;
}	t_tab3x1;

typedef struct s_cardinal
{
	bool	no;
	bool	so;
	bool	we;
	bool	ea;
}	t_cardinal;

typedef struct s_view
{
	t_tab3x1	map;
	void		*textures[4];
	int			nocollide;
	char		*text[4];
	int			texture_width[4];
	int			texture_height[4];
	t_cols		fccolor[2];
	t_cols		*ceil;
	t_cols		*floor;
	t_vec3x1	player;
	float		playerangle;
	int			bpp;
	int			sl;
	int			endian;
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img;
	char		*addr;
	t_cardinal	txtvrf;
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
typedef struct s_vmapcols
{
	int		i;
	char	compass[2][3];
	bool	sense;
	t_errcd	err;
}	t_vmapcols;

// Parsing
void			replacewhitespace(char *str);
void			ft_free_2(t_view *view);
void			init_vmapcols(t_vmapcols *a, int *fd, char **line);
void			allocate_taby(t_view *view, size_t y);
bool			colorisvalid(char *str);
t_errcd			changetxtidx(t_cardinal *vrf, t_view *view);
t_errcd			ft_create_map(char *path, t_view *view);
t_errcd			ft_scanmap(t_tab3x1 map);
void			ft_draw3d_view(t_view *view, int squareproportion);
t_raycast_hit	cast_ray(t_view *view, t_vector2f player_pos,
					float angle, int squareproportion);
int				key_press(int keycode, t_view *view);
void			ft_free_map_end_normal(t_view *view);
void			init_minimap_data(t_minimap_data *data, t_view *view);
void			draw_minimap(t_view *view, int squareproportion);
void			fill_background(t_view *view);
void			draw_line(t_vec3x1 *start, t_vec3x1 *end,
					t_view *view, int col);
void			drawsquare(t_vec3x1 start, t_view *view, int col, int sqprp);
void			init_ray_data(t_ray_data *data,
					t_vector2f player_pos, float angle);
t_raycast_hit	cast_ray(t_view *view, t_vector2f player_pos,
					float angle, int squareproportion);
t_errcd			ft_init_verify_map(char **av, t_view *view);
t_errcd			init_view(t_view *view, char **av);
int				ft_error(t_errcd err, t_view *view);
bool			ft_is_architecture_part(char *line);
bool			ft_good_extension(char *ext, char *ext_expected, int len);
t_errcd			ft_verify_map(int *fd, t_view *view, char *path);
bool			ft_str_is_whitespace(char *str);
t_errcd			ft_size_map_y(char *path, size_t *maxy, size_t *maxx);
t_errcd			ft_verify_colors(char *compass,
					char **line, t_view *view, int j);
t_maptype		ft_define_map_type(char c);
t_errcd			ft_verify_textures(char *line, char **structtext);
void			calculate_new_position(t_move_data *data, t_view *view,
					int keycode);
int				check_wall_collision(t_move_data *data, t_view *view,
					size_t check_x, size_t check_y);
void			init_move_data(t_move_data *data, t_view *view);
int				is_collision(t_move_data *data, size_t check_x, size_t check_y);
t_errcd			ft_verify_map_colors(int *fd, t_view *view, char **line);
void			ft_free_map_partial(t_view *view, size_t y);
#endif
