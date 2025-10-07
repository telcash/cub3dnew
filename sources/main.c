/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfernan3 <dfernan3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 16:31:05 by dfernan3          #+#    #+#             */
/*   Updated: 2025/10/07 17:50:52 by dfernan3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Cube3D.h"

void	print_test(t_data *data)
{
	int h;
	int w;

	printf("Textura NO: %s\n", data->map->no_t);
	printf("Textura SO: %s\n", data->map->so_t);
	printf("Textura EA: %s\n", data->map->ea_t);
	printf("Textura WE: %s\n", data->map->we_t);
	printf("Floor color: (%d, %d, %d)\n", data->map->f->r, data->map->f->g,
		data->map->f->b);
	printf("Ceiling color: (%d, %d, %d)\n", data->map->c->r, data->map->c->g,
		data->map->c->b);
    printf("Maps coors begin in line: %d\n", data->map->coords_fl);
	printf("Width: %zu\n", data->map->w);
    printf("Height: %zu\n", data->map->h);
	printf("Player view direction: %c\n", data->map->player->view);
	printf("Player init row: %d\n", data->map->player->row);
	printf("Player init col: %d\n", data->map->player->col);
	printf("Num spaces: %d\n", data->map->num_spaces);
	printf("Coords: \n");
	h = 0;
	while (data->map->coords[h])
	{
		w = 0;
		while (data->map->coords[h][w])
		{
			printf("%c",data->map->coords[h][w]);
			w++;
		}
		h++;
	}
}

int	main(int ac, char **av)
{
	t_data *data;

	if (ac != 2)
		return (ft_putendl_fd(ERR_NUM_ARGS, 2), 1);
	data = init_data(av[1]);
	if (!data)
		return (1);
	// print_test(data);
	init_game(data);
	return (0);
}
