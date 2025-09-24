/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csalazar <csalazar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:04:25 by csalazar          #+#    #+#             */
/*   Updated: 2025/09/24 17:39:45 by csalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cube3D.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void free_data(t_data *data)
{
    if (data->map)
    {
        if (data->map->no_t)
            free(data->map->no_t);
        if (data->map->so_t)
            free(data->map->so_t);
        if (data->map->ea_t)
            free(data->map->ea_t);
        if (data->map->we_t)
            free(data->map->we_t);
        if (data->map->f)
            free(data->map->f);
        if (data->map->c)
            free(data->map->c);
        if (data->map->coords)
            free_split(data->map->coords);
        if (data->map->player)
            free(data->map->player);
        free(data->map);
    }
    mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
    //ft_destroy_images(t_game *game)
    if (data)
        free(data);
    return ;
}
