/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabejaou <sabejaou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 01:04:57 by sabejaou          #+#    #+#             */
/*   Updated: 2024/09/23 06:02:54 by sabejaou         ###   ########.fr       */
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

// void	ft_drawrays(t_view *view, int squareproportion)
// {
// 	t_vec3x1 end;
// 	t_vec3x1 start;
// 	int x;
// 	int y;

// 	start.x = view->player.x + squareproportion * 0.5;
// 	start.y = view->player.y + squareproportion * 0.5;
// 	x = start.x / squareproportion;
// 	y = start.y / squareproportion;
// 	end.x = start.x + cos(view->playerangle) * 7.0f;
// 	end.y = start.y + sin(view->playerangle) * 7.0f;
// 	printf("Y:%d\n", y);
// 	while (view->map.tab[(int)floor(end.y / squareproportion)][x].type != WALL)
// 		end.y -= 0.1;
// 	draw_line(&start, &end, view, 0x00FF00);
// }

void ft_drawrays(t_view *view, int squareproportion)
{
    t_vec3x1 start;
    t_vec3x1 end;
    float fov;
    int num_rays;
    float ray_angle;
    float max_distance;
    float distance;
    int i;
    size_t map_x;
    size_t map_y;

    fov = M_PI / 3; // 60 degrés de champ de vision
    num_rays = 250; // Nombre de rayons à dessiner
    max_distance = 1000.0f;

    start.x = view->player.x + squareproportion * 0.5;
    start.y = view->player.y + squareproportion * 0.5;

    for (i = 0; i < num_rays; i++)
    {
        ray_angle = view->playerangle - fov / 2 + fov * i / (num_rays - 1);
        end = start;
        distance = 0.0f;

        while (distance < max_distance)
        {
            end.x = start.x + cos(ray_angle) * distance;
            end.y = start.y + sin(ray_angle) * distance;

            map_x = (int)floor(end.x / squareproportion);
            map_y = (int)floor(end.y / squareproportion);

            if (map_x < 0 || map_x >= view->map.maxx || map_y < 0 || map_y >= view->map.maxy)
                break;

            if (view->map.tab[map_y][map_x].type == WALL)
                break;

            distance += 0.1;
        }

        draw_line(&start, &end, view, 0x00FF00);
    }
}
void fill_background(t_view *view, int ceiling_color, int floor_color) {
    for (int y = 0; y < WINDOW_HEIGHT; y++) {
        for (int x = 0; x < WINDOW_WIDTH; x++) {
            int color = (y < WINDOW_HEIGHT / 2) ? ceiling_color : floor_color;
            ((int *)view->addr)[y * (view->sl >> 2) + x] = color;
        }
    }
}

void	drawsquareplayer(t_view *view, int col, int sqprp)
{
	int x;
	int y;
	t_vec3x1 end;
	t_vec3x1 tmp;

	ft_drawrays(view, sqprp);
	x = 0;
	y = 0;
	tmp.x = view->player.x;
	tmp.y = view->player.y;
	while (y <= sqprp)
	{
		end.x = tmp.x + sqprp;
		end.y = tmp.y;
		draw_line(&tmp, &end, view, col);
		tmp.y += 1;
		y++;
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

void draw_minimap(t_view *view, int squareproportion)
{
    int minimap_width = 400; // Largeur de la minimap
    int minimap_height = 400; // Hauteur de la minimap
    int start_x = 10; // Position X dans la fenêtre
    int start_y = 10; // Position Y dans la fenêtre

    // Calculer la taille maximum pour les murs et le joueur
    int wall_size = fmin(minimap_width / view->map.maxx, minimap_height / view->map.maxy);
    int player_size = wall_size; // Utiliser la même taille pour le joueur

    // Dessiner le fond de la minimap
    for (int y = 0; y < minimap_height; y++)
    {
        for (int x = 0; x < minimap_width; x++)
        {
            ((int *)view->addr)[(start_y + y) * (view->sl >> 2) + (start_x + x)] = 0x000000; // Remplir avec noir
        }
    }

    // Dessiner les murs sur la minimap
    for (size_t map_y = 0; map_y < view->map.maxy; map_y++)
    {
        for (size_t map_x = 0; map_x < view->map.maxx; map_x++)
        {
            if (view->map.tab[map_y][map_x].type == WALL)
            {
                // Calculer les coordonnées sur la minimap
                int mini_x = start_x + (map_x * minimap_width / view->map.maxx);
                int mini_y = start_y + (map_y * minimap_height / view->map.maxy);

                // Utiliser drawsquare pour dessiner le mur
                t_vec3x1 wall_position;
                wall_position.x = mini_x;
                wall_position.y = mini_y;
                wall_position.z = 0;

                drawsquare(wall_position, view, 0xFFFFFF, wall_size); // Mur en blanc
            }
        }
    }

    // Dessiner le joueur sur la minimap
    int player_mini_x = start_x + (view->player.x / squareproportion * minimap_width / view->map.maxx);
    int player_mini_y = start_y + (view->player.y / squareproportion * minimap_height / view->map.maxy);
    
    // Utiliser drawsquare pour dessiner le joueur
    t_vec3x1 player_position;
    player_position.x = player_mini_x;
    player_position.y = player_mini_y;
    player_position.z = 0;

    drawsquare(player_position, view, 0xFF0000, player_size); // Joueur en rouge

    // Dessiner la direction du joueur
    float direction_length = player_size * 2; // Longueur de la flèche représentant la direction
    float dir_x = cos(view->playerangle) * direction_length;
    float dir_y = sin(view->playerangle) * direction_length;

    t_vec3x1 direction_start;
    direction_start.x = player_mini_x + player_size * 0.5;
    direction_start.y = player_mini_y + player_size * 0.5;

    t_vec3x1 direction_end;
    direction_end.x = player_mini_x + dir_x;
    direction_end.y = player_mini_y + dir_y;

    draw_line(&direction_start, &direction_end, view, 0xFFFF00); // Flèche en jaune
}

#include <float.h>

typedef struct {
    float x, y;
} Vector2f;

typedef struct {
    float distance;
    int texture_index;
    float wall_x;
} RaycastHit;

RaycastHit cast_ray(t_view *view, Vector2f player_pos, float angle, int squareproportion) {
    Vector2f ray_dir = {cosf(angle), sinf(angle)};
    Vector2f step_size = {
        sqrtf(1 + (ray_dir.y / ray_dir.x) * (ray_dir.y / ray_dir.x)),
        sqrtf(1 + (ray_dir.x / ray_dir.y) * (ray_dir.x / ray_dir.y))
    };
    
    Vector2f map_check = {floorf(player_pos.x), floorf(player_pos.y)};
    Vector2f ray_length_1d = {0, 0};
    Vector2f step = {0, 0};
    
    if (ray_dir.x < 0) {
        step.x = -1;
        ray_length_1d.x = (player_pos.x - map_check.x) * step_size.x;
    } else {
        step.x = 1;
        ray_length_1d.x = (map_check.x + 1 - player_pos.x) * step_size.x;
    }
    
    if (ray_dir.y < 0) {
        step.y = -1;
        ray_length_1d.y = (player_pos.y - map_check.y) * step_size.y;
    } else {
        step.y = 1;
        ray_length_1d.y = (map_check.y + 1 - player_pos.y) * step_size.y;
    }
    
    float distance = 0;
    int hit_vertical = 0;
    int texture_index = 0;
    
    while (1) {
        if (ray_length_1d.x < ray_length_1d.y) {
            map_check.x += step.x;
            distance = ray_length_1d.x;
            ray_length_1d.x += step_size.x;
            hit_vertical = 1;
        } else {
            map_check.y += step.y;
            distance = ray_length_1d.y;
            ray_length_1d.y += step_size.y;
            hit_vertical = 0;
        }
        
        if (map_check.x < 0 || map_check.x >= view->map.maxx || 
            map_check.y < 0 || map_check.y >= view->map.maxy) {
            break;
        }
        
        if (view->map.tab[(int)map_check.y][(int)map_check.x].type == WALL) {
            if (hit_vertical) {
                texture_index = (step.x > 0) ? 3 : 2; // East : West
            } else {
                texture_index = (step.y > 0) ? 1 : 0; // South : North
            }
            break;
        }
    }
    
    float wall_x;
    if (hit_vertical) {
        wall_x = player_pos.y + distance * ray_dir.y;
    } else {
        wall_x = player_pos.x + distance * ray_dir.x;
    }
    wall_x -= floorf(wall_x);
    
    return (RaycastHit){distance * squareproportion, texture_index, wall_x};
}

void ft_draw3d_view(t_view *view, int squareproportion) {
    Vector2f player_pos = {
        view->player.x / squareproportion,
        view->player.y / squareproportion
    };
    
    float fov = M_PI / 3;
    float ray_step = fov / WINDOW_WIDTH;
    
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
        
        double step = (double)view->texture_height[hit.texture_index] / line_height;
        double tex_pos = (draw_start - WINDOW_HEIGHT / 2 + line_height / 2) * step;
        
        for (int y = draw_start; y <= draw_end; y++) {
            int tex_y = (int)tex_pos & (view->texture_height[hit.texture_index] - 1);
            tex_pos += step;
            
            int *texture_data = (int *)mlx_get_data_addr(view->textures[hit.texture_index], &view->bpp, &view->sl, &view->endian);
            int color = texture_data[tex_y * view->texture_width[hit.texture_index] + tex_x];
            
            float darkness = 1.0f - (hit.distance / (20.0f * squareproportion));
            if (darkness < 0) darkness = 0;
            int r = ((color >> 16) & 0xFF) * darkness;
            int g = ((color >> 8) & 0xFF) * darkness;
            int b = (color & 0xFF) * darkness;
            color = (r << 16) | (g << 8) | b;
            
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

    if (view->map.maxy >= view->map.maxx)
        squareproportion = WINDOW_HEIGHT / view->map.maxy;
    else
        squareproportion = WINDOW_HEIGHT / view->map.maxx;

    // Définir la vitesse de déplacement
    move_speed = 5.0f; // Ajustez cette valeur pour augmenter la vitesse

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

        // Vérifier si le mouvement est valide
        size_t map_x = (int)(new_x / squareproportion);
        size_t map_y = (int)(new_y / squareproportion);

        // Vérification des limites de la carte et des collisions
        if (map_x >= 0 && map_x < view->map.maxx && map_y >= 0 && map_y < view->map.maxy)
        {
            // Vérification des collisions avec les murs pour toutes les directions
            if (view->map.tab[map_y][map_x].type != WALL &&
                view->map.tab[map_y][(int)((new_x + squareproportion - 1) / squareproportion)].type != WALL && // Droite
                view->map.tab[(int)((new_y + squareproportion - 1) / squareproportion)][map_x].type != WALL && // Bas
                view->map.tab[(int)((new_y + squareproportion - 1) / squareproportion)][(int)((new_x + squareproportion - 1) / squareproportion)].type != WALL) // Bas-Droite
            {
                view->player.x = new_x; // Mettre à jour la position x
                view->player.y = new_y; // Mettre à jour la position y
            }
        }
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
	ft_print_map_types(view);
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
	printf("%f %f\n", view->player.x, view->player.y);
	view->player.x *= squareproportion;
	view->player.y *= squareproportion;
	ft_draw3d_view(view, squareproportion);
	view->addr = mlx_get_data_addr(view->img, &view->bpp, &view->sl,
			&view->endian);
	draw_minimap(view, squareproportion);
	// draw2dmap(view);
	// drawsquareplayer(view, 0X0000FF, squareproportion);
	mlx_put_image_to_window(view->mlx_ptr, view->win_ptr, view->img, 0, 0);
	mlx_hook(view->win_ptr, 2, 1L << 0, (int (*)())key_press, view);
	mlx_hook(view->win_ptr, 17, 0, (int (*)())ft_free_map_end_normal, view);
	mlx_loop(view->mlx_ptr);
	// ft_free_map(view);
}
