/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlossalazar <carlossalazar@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 08:15:16 by carlossalaz       #+#    #+#             */
/*   Updated: 2025/09/23 09:58:46 by carlossalaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cube3D.h"

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

int key_press(int keycode, t_player *player)
{
    if (keycode == W)
        player->key_up = true;
    if (keycode == A)
        player->key_left = true;
    if (keycode == S)
        player->key_down = true;
    if (keycode == D)
        player->key_right = true;
    return (0);
}

int key_realase(int keycode, t_player *player)
{
    if (keycode == W)
        player->key_up = false;
    if (keycode == A)
        player->key_left = false;
    if (keycode == S)
        player->key_down = false;
    if (keycode == D)
        player->key_right = false;
    return (0);
}

void move_player(t_player *player)
{
    int speed;

    speed = 5;
    if (player->key_up)
        player->pos_y -= speed;
    if (player->key_down)
        player->pos_y += speed;
    if (player->key_right)
        player->pos_x += speed;
    if (player->key_left)
        player->pos_x -= speed;
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

int draw_loop(t_data *data)
{
	move_player(data->map->player);
	clear_image(data);
	draw_square(data->map->player->pos_x, data->map ->player->pos_y, 10, 0x00FF00, data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}

void init_game(t_data *data)
{
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    set_player_init_pos(data);
    mlx_hook(data->win, 2, 1L<<0, key_press, data->map->player);
    mlx_hook(data->win, 3, 1L<<1, key_realase, data->map->player);
    mlx_loop_hook(data ->mlx, draw_loop, data);
}