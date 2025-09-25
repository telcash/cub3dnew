/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csalazar <csalazar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 08:15:16 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/09/24 17:35:31 by csalazar         ###   ########.fr       */
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

    // Rotación
    if (player->left_rotate)
        player->angle -= angle_speed;
    if (player->right_rotate)
        player->angle += angle_speed;

    // Normalizar ángulo entre 0 y 2π
    if (player->angle > 2 * PI)
        player->angle -= 2 * PI;
    if (player->angle < 0)
        player->angle += 2 * PI;

    // Movimiento adelante/atrás
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

    // Movimiento lateral (strafe)
    if (player->key_left)
    {
        player->pos_x -= sin_angle * speed;
        player->pos_y += cos_angle * speed;
    }
    if (player->key_right)
    {
        player->pos_x += sin_angle * speed;
        player->pos_y -= cos_angle * speed;
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

bool touch(float px, float py, t_data *data)
{
    int x;
    int y;

    x = px / BLOCK;
    y = py / BLOCK;
    if(data->map->coords[y][x] == '1')
        return true;
    return false;
}

int draw_loop(t_data *data)
{
    t_player *player = data->map->player;
    float ray_x;
    float ray_y;
    float cos_angle;
    float sin_angle;

	move_player(player);
	clear_image(data);
    draw_square(player->pos_x, player->pos_y, 10, 0x00FF00, data);
	draw_map(data);
	ray_x = player->pos_x;
    ray_y = player->pos_y;
    cos_angle = cos(player->angle);
    sin_angle = sin(player->angle);
    while(!touch(ray_x, ray_y, data))
    {
        put_pixel(ray_x, ray_y, 0xFF0000, data);
        ray_x += cos_angle;
        ray_y += sin_angle;
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