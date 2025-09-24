/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csalazar <csalazar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 10:04:47 by csalazar          #+#    #+#             */
/*   Updated: 2025/09/24 17:19:33 by csalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cube3D.h"

static t_player *init_player()
{
    t_player *player;

    player = malloc(sizeof(t_player));
    if (!player)
        return (ft_putendl_fd(ERR_MALLOC_PLAYER, 2), NULL);
    player->col = 0;
    player->row = 0;
    player->view = '\0';
    player->pos_x = 0.0;
    player->pos_y = 0.0;
    player->dir_x = 0.0;
    player->dir_y = 0.0;
    player->plane_x = 0.0;
    player->plane_y = 0.0;
    player->key_up = false;
    player->key_down = false;
    player->key_left = false;
    player->key_right = false;
    return (player);
}

static t_map *init_map()
{
    t_map *map;

    map = malloc(sizeof(t_map));
    if (!map)
        return (ft_putendl_fd(ERR_MALLOC_MAP, 2), NULL);
    map->h = 0;
    map->w = 0;
    map->coords_fl = 0;
    map->num_spaces = 0;
    map->no_t = NULL;
    map->so_t = NULL;
    map->we_t = NULL;
    map->ea_t = NULL;
    map->f = NULL;
    map->c = NULL;
    map->coords = NULL;
    map->player = init_player();
    if (!map->player)
        return (NULL);
    return (map);
}

t_data *init_data(char *file)
{
    t_data *data;
    
    data = malloc(sizeof(t_data));
    if (!data)
        return (ft_putendl_fd(ERR_MALLOC_DATA, 2), NULL);
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cube3D");
    data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    data->addr = mlx_get_data_addr(data->img, &data->bpp, &data->line_len, &data->endian);
    data->map = NULL;
    data->map = init_map();
    if (!data->map || parse_map(data->map, file))
        return (free_data(data), NULL);
    return (data);
}
