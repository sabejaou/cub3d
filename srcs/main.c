/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabejaou <sabejaou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 01:04:57 by sabejaou          #+#    #+#             */
/*   Updated: 2024/09/23 07:51:22 by sabejaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3d.h"

void load_textures(t_view *view)
{
    for (int i = 0; i < 4; i++)
    {
        view->textures[i] = mlx_xpm_file_to_image(view->mlx_ptr, view->text[i], 
                                                  &view->texture_width[i], 
                                                  &view->texture_height[i]);
        if (!view->textures[i])
        {
            fprintf(stderr, "Error loading texture: %s\n", view->text[i]);
            exit(EXIT_FAILURE);
        }
    }
}

void	ft_free_map_end_normal(t_view *view)
{
	size_t y;

	y = 0;
	while(view->map.tab && y < view->map.maxy)
	{
			if (view->map.tab[y])
				free(view->map.tab[y]);
			y++;
	}
	y = 0;
	while(y < 4)
	{
		if (view->text[y])
			free(view->text[y]);
		y++;
	}
	if (view->map.tab)
		free(view->map.tab);
	mlx_destroy_image(view->mlx_ptr, view->img);
	mlx_destroy_window(view->mlx_ptr, view->win_ptr);
	mlx_destroy_display(view->mlx_ptr);
	free(view->mlx_ptr);
	if (view)
		free(view);
	exit(0);
}

void	ft_free_map(t_view *view)
{
	size_t y;

	y = 0;
	while(view->map.tab && y < view->map.maxy)
	{
			if (view->map.tab[y])
				free(view->map.tab[y]);
			y++;
	}
	y = 0;
	while(y < 4)
	{
		if (view->text[y])
			free(view->text[y]);
		y++;
	}
	if (view->map.tab)
		free(view->map.tab);
	if (view)
		free(view);
}

void	draw_lineplayer(t_vec3x1 *start, t_vec3x1 *end, t_view *view, int col)
{
	t_drawlineutils u;

	u.i = 0;
	u.dx = end->x - start->x;
	u.dy = end->y - start->y;
	if (fabs(u.dx) > fabs(u.dy))
		u.steps = fabs(u.dx);
	else
		u.steps = fabs(u.dy);
	u.x_inc = u.dx / (float)u.steps;
	u.y_inc = u.dy / (float)u.steps;
	u.x = start->x;
	u.y = start->y;
	while (u.i <= u.steps)
	{
		if (u.x >= 0 && u.y >= 0 && u.x < WINDOW_WIDTH - 4
			&& u.y < WINDOW_HEIGHT - 4)
			((int *)view->addr)[(int)u.y * (view->sl >> 2)
				+ (int)u.x] = col;
		u.x += u.x_inc;
		u.y += u.y_inc;
		u.i++;
	}
}

void	draw_line(t_vec3x1 *start, t_vec3x1 *end, t_view *view, int col)
{
	t_drawlineutils u;

	u.i = 0;
	u.dx = end->x - start->x;
	u.dy = end->y - start->y;
	if (fabs(u.dx) > fabs(u.dy))
		u.steps = fabs(u.dx);
	else
		u.steps = fabs(u.dy);
	u.x_inc = u.dx / (float)u.steps;
	u.y_inc = u.dy / (float)u.steps;
	u.x = start->x;
	u.y = start->y;
	while (u.i <= u.steps)
	{
		if (u.x >= 0 && u.y >= 0 && u.x < WINDOW_WIDTH - 4
			&& u.y < WINDOW_HEIGHT - 4)
			((int *)view->addr)[(int)u.y * (view->sl >> 2)
				+ (int)u.x] = col;
		u.x += u.x_inc;
		u.y += u.y_inc;
		u.i++;
	}
}

void	drawsquare(t_vec3x1 start, t_view *view, int col, int sqprp)
{
	int x;
	int y;
	t_vec3x1 end;
	t_vec3x1 tmp;

	x = 0;
	y = 0;
	tmp.x = start.x;
	tmp.y = start.y;
	while (y <= sqprp)
	{
		end.x = start.x + sqprp;
		end.y = tmp.y;
		draw_line(&tmp, &end, view, col);
		tmp.y += 1;
		y++;
	}
}

void init_minimap_data(t_minimap_data *data, t_view *view)
{
	data->minimap_width = 400;
	data->minimap_height = 400;
	data->start_x = 10;
	data->start_y = 10;
	data->wall_size = fmin(data->minimap_width / view->map.maxx, data->minimap_height / view->map.maxy);
	data->player_size = data->wall_size;
}

void draw_minimap_background(t_view *view, t_minimap_data *data)
{
	int x;
	int y;

	y = 0;
	while (y < data->minimap_height)
	{
		x = 0;
		while (x < data->minimap_width)
		{
			((int *)view->addr)[(data->start_y + y) * (view->sl >> 2) + (data->start_x + x)] = 0x000000;
			x++;
		}
		y++;
	}
}

void draw_minimap_walls(t_view *view, t_minimap_data *data)
{
	size_t map_x;
	size_t map_y;
	int mini_x;
	int mini_y;
	t_vec3x1 wall_position;

	map_y = 0;
	while (map_y < view->map.maxy)
	{
		map_x = 0;
		while (map_x < view->map.maxx)
		{
			if (view->map.tab[map_y][map_x].type == WALL)
			{
				mini_x = data->start_x + (map_x * data->minimap_width / view->map.maxx);
				mini_y = data->start_y + (map_y * data->minimap_height / view->map.maxy);
				wall_position.x = mini_x;
				wall_position.y = mini_y;
				wall_position.z = 0;
				drawsquare(wall_position, view, 0xFFFFFF, data->wall_size);
			}
			map_x++;
		}
		map_y++;
	}
}

void draw_minimap_player(t_view *view, t_minimap_data *data, int squareproportion)
{
	int player_mini_x;
	int player_mini_y;
	t_vec3x1 player_position;

	player_mini_x = data->start_x + (view->player.x / squareproportion * data->minimap_width / view->map.maxx);
	player_mini_y = data->start_y + (view->player.y / squareproportion * data->minimap_height / view->map.maxy);
	player_position.x = player_mini_x;
	player_position.y = player_mini_y;
	player_position.z = 0;
	drawsquare(player_position, view, 0xFF0000, data->player_size);
}

void draw_player_direction(t_view *view, t_minimap_data *data, int player_mini_x, int player_mini_y)
{
	float direction_length;
	float dir_x;
	float dir_y;
	t_vec3x1 direction_start;
	t_vec3x1 direction_end;

	direction_length = data->player_size * 2;
	dir_x = cos(view->playerangle) * direction_length;
	dir_y = sin(view->playerangle) * direction_length;
	direction_start.x = player_mini_x + data->player_size * 0.5;
	direction_start.y = player_mini_y + data->player_size * 0.5;
	direction_end.x = player_mini_x + dir_x;
	direction_end.y = player_mini_y + dir_y;
	draw_line(&direction_start, &direction_end, view, 0xFFFF00);
}

void draw_minimap(t_view *view, int squareproportion)
{
	t_minimap_data data;
	int player_mini_x;
	int player_mini_y;

	init_minimap_data(&data, view);
	draw_minimap_background(view, &data);
	draw_minimap_walls(view, &data);
	draw_minimap_player(view, &data, squareproportion);
	player_mini_x = data.start_x + (view->player.x / squareproportion * data.minimap_width / view->map.maxx);
	player_mini_y = data.start_y + (view->player.y / squareproportion * data.minimap_height / view->map.maxy);
	draw_player_direction(view, &data, player_mini_x, player_mini_y);
}

void fill_background(t_view *view)
{
    int ceiling_color;
	int	floor_color;
    
    ceiling_color = (view->ceil->r << 16) | (view->ceil->g << 8) | view->ceil->b;
    floor_color = (view->floor->r << 16) | (view->floor->g << 8) | view->floor->b;
    for (int y = 0; y < WINDOW_HEIGHT; y++)
    {
        for (int x = 0; x < WINDOW_WIDTH; x++)
        {
            int color = (y < WINDOW_HEIGHT / 2) ? ceiling_color : floor_color;
            ((int *)view->addr)[y * (view->sl >> 2) + x] = color;
        }
    }
}

void init_ray_data(t_ray_data *data, Vector2f player_pos, float angle)
{
	data->ray_dir.x = cosf(angle);
	data->ray_dir.y = sinf(angle);
	data->step_size.x = sqrtf(1 + (data->ray_dir.y / data->ray_dir.x) * (data->ray_dir.y / data->ray_dir.x));
	data->step_size.y = sqrtf(1 + (data->ray_dir.x / data->ray_dir.y) * (data->ray_dir.x / data->ray_dir.y));
	data->map_check.x = floorf(player_pos.x);
	data->map_check.y = floorf(player_pos.y);
	data->ray_length_1d.x = 0;
	data->ray_length_1d.y = 0;
	data->step.x = 0;
	data->step.y = 0;
	data->distance = 0;
	data->hit_vertical = 0;
	data->texture_index = 0;
}

void calculate_step_and_ray_length(t_ray_data *data, Vector2f player_pos)
{
	if (data->ray_dir.x < 0)
	{
		data->step.x = -1;
		data->ray_length_1d.x = (player_pos.x - data->map_check.x) * data->step_size.x;
	}
	else
	{
		data->step.x = 1;
		data->ray_length_1d.x = (data->map_check.x + 1 - player_pos.x) * data->step_size.x;
	}

	if (data->ray_dir.y < 0)
	{
		data->step.y = -1;
		data->ray_length_1d.y = (player_pos.y - data->map_check.y) * data->step_size.y;
	}
	else
	{
		data->step.y = 1;
		data->ray_length_1d.y = (data->map_check.y + 1 - player_pos.y) * data->step_size.y;
	}
}

int check_wall_hit(t_ray_data *data, t_view *view)
{
	if (data->map_check.x < 0 || data->map_check.x >= view->map.maxx || 
		data->map_check.y < 0 || data->map_check.y >= view->map.maxy)
	{
		return 1;
	}

	if (view->map.tab[(int)data->map_check.y][(int)data->map_check.x].type == WALL)
	{
		if (data->hit_vertical)
		{
			data->texture_index = (data->step.x > 0) ? 3 : 2;
		}
		else
		{
			data->texture_index = (data->step.y > 0) ? 1 : 0;
		}
		return 1;
	}
	return 0;
}

void perform_dda(t_ray_data *data, t_view *view)
{
	int hit;

	hit = 0;
	while (!hit)
	{
		if (data->ray_length_1d.x < data->ray_length_1d.y)
		{
			data->map_check.x += data->step.x;
			data->distance = data->ray_length_1d.x * 0.1;
			data->ray_length_1d.x += data->step_size.x;
			data->hit_vertical = 1;
		}
		else
		{
			data->map_check.y += data->step.y;
			data->distance = data->ray_length_1d.y * 0.1;
			data->ray_length_1d.y += data->step_size.y;
			data->hit_vertical = 0;
		}
		hit = check_wall_hit(data, view);
	}
}

RaycastHit calculate_hit_point(t_ray_data *data, Vector2f player_pos, int squareproportion)
{
	float exact_hit_x;
	float exact_hit_y;
	float wall_x;

	if (data->hit_vertical)
	{
		exact_hit_x = data->map_check.x;
		exact_hit_y = player_pos.y + (data->map_check.x - player_pos.x) * data->ray_dir.y / data->ray_dir.x;
		wall_x = exact_hit_y - floor(exact_hit_y);
	}
	else
	{
		exact_hit_y = data->map_check.y;
		exact_hit_x = player_pos.x + (data->map_check.y - player_pos.y) * data->ray_dir.x / data->ray_dir.y;
		wall_x = exact_hit_x - floor(exact_hit_x);
	}

	return (RaycastHit){data->distance * squareproportion, data->texture_index, wall_x, (int)data->map_check.x, (int)data->map_check.y};
}

RaycastHit cast_ray(t_view *view, Vector2f player_pos, float angle, int squareproportion)
{
	t_ray_data data;

	init_ray_data(&data, player_pos, angle);
	calculate_step_and_ray_length(&data, player_pos);
	perform_dda(&data, view);
	return calculate_hit_point(&data, player_pos, squareproportion);
}

void ft_draw3d_view(t_view *view, int squareproportion) {
    Vector2f player_pos = {
        view->player.x / squareproportion,
        view->player.y / squareproportion
    };
    
    float fov = M_PI / 3;
    float ray_step = fov / WINDOW_WIDTH;
	view->addr = mlx_get_data_addr(view->img, &view->bpp, &view->sl, &view->endian);
    for (int x = 0; x < WINDOW_WIDTH; x++) {
        float ray_angle = view->playerangle - fov / 2 + x * ray_step;
        
        RaycastHit hit = cast_ray(view, player_pos, ray_angle, squareproportion);
        
        float perp_distance = hit.distance * cosf(ray_angle - view->playerangle);
        int line_height = (int)(WINDOW_HEIGHT / perp_distance);
        
        int draw_start = -line_height / 2 + WINDOW_HEIGHT / 2;
        if (draw_start < 0) draw_start = 0;
        int draw_end = line_height / 2 + WINDOW_HEIGHT / 2;
        if (draw_end >= WINDOW_HEIGHT) draw_end = WINDOW_HEIGHT - 1;
        
        int tex_x = (int)(hit.wall_x * view->texture_width[hit.texture_index]);
        if (hit.texture_index == 2 || hit.texture_index == 3) {
            tex_x = view->texture_width[hit.texture_index] - tex_x - 1;
        }
        
        double step = 1.0 * view->texture_height[hit.texture_index] / line_height;
        double tex_pos = (draw_start - WINDOW_HEIGHT / 2 + line_height / 2) * step;
        
        for (int y = draw_start; y <= draw_end; y++) {
            int tex_y = (int)tex_pos & (view->texture_height[hit.texture_index] - 1);
            tex_pos += step;
            
            int *texture_data = (int *)mlx_get_data_addr(view->textures[hit.texture_index], &view->bpp, &view->sl, &view->endian);
            int color = texture_data[tex_y * view->texture_width[hit.texture_index] + tex_x];

            view->addr = mlx_get_data_addr(view->img, &view->bpp, &view->sl, &view->endian);
            ((int *)view->addr)[y * (view->sl >> 2) + x] = color;
        }
    }
}

int key_press(int keycode, t_view *view)
{
    int squareproportion;
    float move_speed;
    float new_x, new_y;
    float hitbox_radius; // Rayon de la hitbox du joueur

    if (view->map.maxy >= view->map.maxx)
        squareproportion = WINDOW_HEIGHT / view->map.maxy;
    else
        squareproportion = WINDOW_HEIGHT / view->map.maxx;

    // Définir la vitesse de déplacement
    move_speed = 5.0f;

    // Définir le rayon de la hitbox (plus petit que la moitié d'un carré)
    hitbox_radius = squareproportion * 0.3f; // Par exemple, 30% de la taille d'un carré

    // Calculer les nouvelles positions basées sur l'angle de vue
    if (keycode == W_KEY || keycode == S_KEY || keycode == A_KEY || keycode == D_KEY)
    {
        new_x = view->player.x;
        new_y = view->player.y;

        // Avancer
        if (keycode == W_KEY)
        {
            new_x += cos(view->playerangle) * move_speed;
            new_y += sin(view->playerangle) * move_speed;
        }
        // Reculer
        else if (keycode == S_KEY)
        {
            new_x -= cos(view->playerangle) * move_speed;
            new_y -= sin(view->playerangle) * move_speed;
        }
        // Déplacement latéral gauche
        else if (keycode == A_KEY)
        {
            new_x -= sin(view->playerangle) * move_speed;
            new_y += cos(view->playerangle) * move_speed;
        }
        // Déplacement latéral droit
        else if (keycode == D_KEY)
        {
            new_x += sin(view->playerangle) * move_speed;
            new_y -= cos(view->playerangle) * move_speed;
        }

        // Vérifier les collisions avec la nouvelle hitbox
        int map_x = new_x / squareproportion;
        int map_y = new_y / squareproportion;

        // Vérifier les cases adjacentes
        for (int dy = -1; dy <= 1; dy++)
        {
            for (int dx = -1; dx <= 1; dx++)
            {
                size_t check_x = map_x + dx;
                size_t check_y = map_y + dy;

                if (check_x >= 0 && check_x < view->map.maxx && check_y >= 0 && check_y < view->map.maxy)
                {
                    if (view->map.tab[check_y][check_x].type == WALL)
                    {
                        // Calculer la distance entre le centre du joueur et le coin le plus proche du mur
                        float wall_center_x = (check_x + 0.5f) * squareproportion;
                        float wall_center_y = (check_y + 0.5f) * squareproportion;
                        float dx = fmaxf(fabsf(new_x - wall_center_x) - squareproportion / 2, 0);
                        float dy = fmaxf(fabsf(new_y - wall_center_y) - squareproportion / 2, 0);
                        float distance = sqrtf(dx * dx + dy * dy);

                        // Si la distance est inférieure au rayon de la hitbox, empêcher le mouvement
                        if (distance < hitbox_radius)
                        {
                            return (0);
                        }
                    }
                }
            }
        }

        // Si aucune collision n'est détectée, mettre à jour la position du joueur
        view->player.x = new_x;
        view->player.y = new_y;
    }
    else if (keycode == A_ARROW_KEY)
    {
        view->playerangle -= ROTATE_SPEED; // Rotation à gauche
    }
    else if (keycode == D_ARROW_KEY)
    {
        view->playerangle += ROTATE_SPEED; // Rotation à droite
    }
    else if (keycode == ESC_KEY)
    {
        ft_free_map_end_normal(view);
    }

    mlx_destroy_image(view->mlx_ptr, view->img);
    view->img = mlx_new_image(view->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
    view->addr = mlx_get_data_addr(view->img, &view->bpp, &view->sl, &view->endian);
    fill_background(view);
    ft_draw3d_view(view, squareproportion);
	view->addr = mlx_get_data_addr(view->img, &view->bpp, &view->sl, &view->endian);
    draw_minimap(view, squareproportion);
    
    mlx_put_image_to_window(view->mlx_ptr, view->win_ptr, view->img, 0, 0);
    
    return 0;
}

int ft_error(t_errcd err, t_view *view)
{
	printf("ERROR:%d\n", err);
	if (err == ERR_ARGS_NBR)
		ft_putendl_fd("Cub3d: Args number invalid\n", 2);
	if (err == ERR_ACCESS_MAP)
		ft_putendl_fd("Cub3d: Can't access path of the map\n", 2);
	if (err == ERR_INVALID_MAP)
		ft_putendl_fd("Cub3d: Map is invalid\n", 2);
	if (err == ERR_FILE_CONSTRUCTION)
		ft_putendl_fd("Cub3d: File is not formated as expected\n", 2);
	if (err == ERR_ACCESS_TEXTURE)
		ft_putendl_fd("Cub3d: Texture file can't be opened\n", 2);
	if (err == ERR_COLOR_FORMAT)
		ft_putendl_fd("Cub3d: Bad colors format\n", 2);
	if (err == ERR_FORMAT_TEXTURE)
		ft_putendl_fd("Cub3d: Bad texture format\n", 2);
	if (err == ERR_ACCESS_MAP)
		ft_putendl_fd("Cub3d: Map can't be opened\n", 2);
	if (err == ERR_EXTENSION_MAP)
		ft_putendl_fd("Cub3d: Map extension is wrong\n", 2);
	if (err == ERR_MLX)
		ft_putendl_fd("Cub3d: MLX_ERROR\n", 2);
	if (err != NO_ERROR)
		ft_free_map(view);
	return (err);
}


void	ft_print_map_types(t_view *view)
{
	size_t x;
	size_t y;

	x = 0;
	y = 0;
	while(y < view->map.maxy)
	{
		while (x < view->map.maxx)
		{
			printf("%d", view->map.tab[y][x].type);
			x++;
		}
		printf("\n");
		y++;
		x = 0;
	}
}

t_errcd ft_init_verify_map(char **av, t_view *view)
{
	t_errcd	err;
	
	err = NO_ERROR;
	err = ft_create_map(av[1], view);
	if (err != NO_ERROR)
		return (ft_error(err, view));
	// ft_print_map_types(view);
	err = ft_scanmap(view->map);
	if (err != NO_ERROR)
		return (ft_error(err, view));
	return (err);
	
}
t_errcd	init_view(t_view *view, char **av)
{
	t_errcd	err;
	
	err = NO_ERROR;
	err = ft_init_verify_map(av, view);
	if (err)
		return (err);
	view->mlx_ptr = mlx_init();
	if (view->mlx_ptr == NULL)
		return (ERR_MLX);
	view->win_ptr = mlx_new_window(view->mlx_ptr,
			WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D - 42");
	if (view->win_ptr == NULL)
		return (ERR_MLX);
	view->img = mlx_new_image(view->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	view->addr = mlx_get_data_addr(view->img, &view->bpp, &view->sl,
			&view->endian);
	if (view->player.type == SPAWN_NORTH)
		view->playerangle = 3 * M_PI / 2;
	else if(view->player.type == SPAWN_SOUTH)
		view->playerangle = M_PI / 2;
	else if (view->player.type == SPAWN_WEST)
		view->playerangle = M_PI;
	else if (view->player.type == SPAWN_EAST)
		view->playerangle = 0;
	load_textures(view);
	return(err);
}

int	main(int ac, char **av)
{
	t_view *view;
	t_errcd	err;
	int squareproportion;
	
	view = ft_calloc(1, sizeof(t_view));
	err = NO_ERROR;
	if (ac != 2)
		return(ft_error(ERR_ARGS_NBR, view));
	err = init_view(view, av);
	if (err)
		return (err);
	if (view->map.maxy >= view->map.maxx)
		squareproportion = WINDOW_HEIGHT / view->map.maxy;
	else
		squareproportion = WINDOW_HEIGHT / view->map.maxx;
	// printf("%f %f\n", view->player.x, view->player.y);
	view->player.x *= squareproportion;
	view->player.y *= squareproportion;
	fill_background(view);
	ft_draw3d_view(view, squareproportion);
	view->addr = mlx_get_data_addr(view->img, &view->bpp, &view->sl,
			&view->endian);
	draw_minimap(view, squareproportion);
	// draw2dmap(view);
	// drawsquareplayer(view, 0X0000FF, squareproportion);
	mlx_put_image_to_window(view->mlx_ptr, view->win_ptr, view->img, 0, 0);
	mlx_hook(view->win_ptr, 2, 1L << 0, (int (*)())key_press, view);
	// mlx_hook(view->win_ptr, 2, 1L << 0, (int (*)())key_release, view);
	mlx_hook(view->win_ptr, 17, 0, (int (*)())ft_free_map_end_normal, view);
	mlx_loop(view->mlx_ptr);
	// ft_free_map(view);
}
