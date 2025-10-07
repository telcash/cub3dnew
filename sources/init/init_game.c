/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfernan3 <dfernan3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 08:15:16 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/10/07 17:54:27 by dfernan3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cube3D.h"

int	ft_close_game(t_data *data)
{
	free_data(data);
	exit(EXIT_FAILURE);
}
void set_player_init_pos(t_data *data)
{
    data->map->player->pos_x = data->map->player->col + 0.5;
    data->map->player->pos_y = data->map->player->row + 0.5;
    if (data->map->player->view == 'N')
    {
        data->map->player->dir_x = -1.0;
        data->map->player->dir_y = 0.0;
        data->map->player->plane_x = 0.0;
        data->map->player->plane_y = 0.66;
    }        
    else if (data->map->player->view == 'S')
    {
        data->map->player->dir_x = 1.0;
        data->map->player->dir_y = 0.0;
        data->map->player->plane_x = 0.0;
        data->map->player->plane_y = -0.66;
    }
    else if (data->map->player->view == 'E')
    {
        data->map->player->dir_x = 0.0;
        data->map->player->dir_y = 1.0;
        data->map->player->plane_x = 0.66;
        data->map->player->plane_y = 0.0;
    }
    else if (data->map->player->view == 'W')
    {
        data->map->player->dir_x = 0.0;
        data->map->player->dir_y = -1.0;
        data->map->player->plane_x = -0.66;
        data->map->player->plane_y = 0.0;
    }
}

int key_press(int keycode, t_data *data)
{
    if (keycode == W)
        data->map->player->key_up = true;
    if (keycode == A)
        data->map->player->key_left = true;
    if (keycode == S)
        data->map->player->key_down = true;
    if (keycode == D)
        data->map->player->key_right = true;
    if (keycode == LEFT)
        data->map->player->left_rotate = true;
    if (keycode == RIGHT)
        data->map->player->right_rotate = true;
    if (keycode == KEY_ESC || keycode == KEY_Q)
		ft_close_game(data);
    return (0);
}

int key_realase(int keycode, t_data *data)
{
    if (keycode == W)
        data->map->player->key_up = false;
    if (keycode == A)
        data->map->player->key_left = false;
    if (keycode == S)
        data->map->player->key_down = false;
    if (keycode == D)
        data->map->player->key_right = false;
    if (keycode == LEFT)
        data->map->player->left_rotate = false;
    if (keycode == RIGHT)
        data->map->player->right_rotate = false;
    return (0);
}

void move_player(t_player *player)
{
    int speed = 3;
    float angle_speed = 0.03;
    float cos_angle = cos(player->angle);
    float sin_angle = sin(player->angle);

    if (player->left_rotate)
        player->angle -= angle_speed;
    if (player->right_rotate)
        player->angle += angle_speed;
    if (player->angle > 2 * PI)
        player->angle = 0;
    if (player->angle < 0)
        player->angle = 2 * PI;
    if (player->key_up)
    {
        player->pos_x += cos_angle * speed;
        player->pos_y += sin_angle * speed;
    }
    if (player->key_down)
    {
        player->pos_x -= cos_angle * speed;
        player->pos_y -= sin_angle * speed;
    }
    if (player->key_left)
    {
        player->pos_x += sin_angle * speed;
        player->pos_y -= cos_angle * speed;
    }
    if (player->key_right)
    {
        player->pos_x -= sin_angle * speed;
        player->pos_y += cos_angle * speed;
    }
}

void put_pixel(int x, int y, int color, t_data *data) //dibuja pixel con el color dado
{
	int i;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return;

	i = y * data->line_len + x * data->bpp / 8;
	data->addr[i] = color & 0xFF;
	data->addr[i + 1] = (color >> 8) & 0xFF;
	data->addr[i + 2] = (color >> 16) & 0xFF;
}

void	clear_image(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(x, y, 0, data);
			x++;
		}
		y++;
	}
}

void draw_square(int x, int y, int size, int color, t_data *data) //dibuja un cuadrado
{
	int i;

	i = 0;
	while (i < size) //cada una es cada linea del cuadrado
	{
		put_pixel(x + i, y, color, data);
		i++;
	}
	i = 0;
	while (i < size)
	{
		put_pixel(x, y + i, color, data);
		i++;
	}
	i = 0;
	while (i < size)
	{
		put_pixel(x + i, y + i, color, data);
		i++;
	}
	i = 0;
	while (i < size)
	{
		put_pixel(x + size, y + i, color, data);
		i++;
	}
	i = 0;
	while (i < size)
	{
		put_pixel(x + i, y + size, color, data);
		i++;
	}
}

void draw_map(t_data *data)
{
    char **map = data->map->coords;
    int color = 0x0000FF;
    int y = 0;

    while (map[y])
    {
        int x = 0;
        while (map[y][x])
        {
            if (map[y][x] == '1')
                draw_square(x * BLOCK, y * BLOCK, BLOCK, color, data);
            x++;
        }
        y++;
    }
}

float distance(float x, float y){
    return sqrt(x * x + y * y);
}

float fixed_dist(float x1, float y1, float x2, float y2, t_data *data)
{
    float delta_x = x2 - x1;
    float delta_y = y2 - y1;
    float angle = atan2(delta_y, delta_x) - data->map->player->angle;
    float fix_dist = distance(delta_x, delta_y) * cos(angle);
    return fix_dist;
}


bool touch(float px, float py, t_data *data)
{
    int x = px / BLOCK;
    int y = py / BLOCK;

    // Check bounds
    if (y < 0 || !data->map->coords[y])
        return true;
    int row_len = ft_strlen(data->map->coords[y]);
    if (x < 0 || x >= row_len)
        return true;

    if (data->map->coords[y][x] == '1')
        return true;
    return false;
}

// raycasting functions
void draw_line(t_player *player, t_data *data, float start_x, int i)
{
    float ray_x;
    float ray_y;
    float cos_angle;
    float sin_angle;

    ray_x = player->pos_x;
    ray_y = player->pos_y;
    cos_angle = cos(start_x);
    sin_angle = sin(start_x);
    while(!touch(ray_x, ray_y, data))
    {
        if (DEBUG)
            put_pixel(ray_x, ray_y, 0xFF0000, data);
        ray_x += cos_angle;
        ray_y += sin_angle;
    }
    if(!DEBUG)
    {
        float dist = fixed_dist(player->pos_x, player->pos_y, ray_x, ray_y, data);
        float height = (BLOCK / dist) * (WIDTH / 2);
        int start_y = (HEIGHT - height) / 2;
        int end = start_y + height;
        while(start_y < end)
        {
            put_pixel(i, start_y, 255, data);
            start_y++;
        }
    }
}

int draw_loop(t_data *data)
{
    t_player *player = data->map->player;
    float fraction;
    float start_x;
    int i;

	move_player(player);
	clear_image(data);
    if (DEBUG)
    {
        draw_square(player->pos_x, player->pos_y, 10, 0x00FF00, data);
        draw_map(data);
    }
    fraction = PI / 3 / WIDTH;
    start_x = player->angle - PI / 6;
    i = 0;
    while(i < WIDTH)
    {
        draw_line(player, data, start_x, i);
        start_x += fraction;
        i++;
    }
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}

void init_game(t_data *data)
{
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    set_player_init_pos(data);
    mlx_hook(data->win, 2, 1L<<0, key_press, data);
    mlx_hook(data->win, 3, 1L<<1, key_realase, data);
    mlx_loop_hook(data->mlx, draw_loop, data);
    mlx_loop(data->mlx);
}