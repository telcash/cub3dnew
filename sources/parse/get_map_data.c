/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfernan3 <dfernan3@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 10:42:04 by csalazar          #+#    #+#             */
/*   Updated: 2025/10/07 17:25:20 by dfernan3         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cube3D.h"

static int	get_map_size(t_map *map, char *line, int lines_readed)
{
	int	j;

	j = 0;
	while (line[j])
	{
		if (!(ft_isspace(line[j]) || line[j] == '1' || line[j] == '0'
				|| ft_is_coord(line[j])))
			return (ft_putendl_fd(BAD_DATA_FORMAT, 2), 1);
		if (line[j] == '0' || ft_is_coord(line[j]))
			map->num_spaces = map->num_spaces + 1;
        if (ft_is_coord(line[j]))
        {
            if (map->player->view)
                return (ft_putendl_fd(DUP_PLAYER, 2), 1);
            map->player->view = line[j];
			map->player->row = lines_readed - map->coords_fl;
			map->player->col = j;
        }
        j++;
	}
	map->h = map->h + 1;
	if (ft_strlen(line) - 1 > map->w)
		map->w = ft_strlen(line) - 1;
	return (0);
}

static int	get_map_params(t_map *map, char *line, int i)
{
	if (line[i] == 'N' && line[i + 1] && line[i + 1] == 'O')
		return (get_texture_from_line(line, i + 2, &map->no_t));
	if (line[i] == 'S' && line[i + 1] && line[i + 1] == 'O')
		return (get_texture_from_line(line, i + 2, &map->so_t));
	if (line[i] == 'W' && line[i + 1] && line[i + 1] == 'E')
		return (get_texture_from_line(line, i + 2, &map->we_t));
	if (line[i] == 'E' && line[i + 1] && line[i + 1] == 'A')
		return (get_texture_from_line(line, i + 2, &map->ea_t));
	if (line[i] == 'F')
		return (get_color_from_line(line, i + 1, &map->f));
	if (line[i] == 'C')
		return (get_color_from_line(line, i + 1, &map->c));
	return (ft_putendl_fd(BAD_DATA_FORMAT, 2), 1);
}

static int	get_data_from_line(t_map *map, char *line, int *is_coords,
		int lines_readed)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (!line[i])
	{
		if (*is_coords == 1)
			*is_coords = 2;
		return (0);
	}
	if (*is_coords == 0 && line[i] == '1')
	{
		map->coords_fl = lines_readed;
		*is_coords = 1;
	}
	if (!*is_coords)
		return (get_map_params(map, line, i));
	if (*is_coords == 2)
		return (ft_putendl_fd(BAD_DATA_FORMAT, 2), 1);
	return (get_map_size(map, line, lines_readed));
}

int	get_map_data(t_map *map, char *file)
{
	int		fd;
	char	*line;
	int		is_coords;
	int		lines_readed;

	is_coords = 0;
	lines_readed = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (ft_putendl_fd(ERR_OPEN_FILE, 2), 1);
	line = get_next_line(fd);
	while (line)
	{
		if (get_data_from_line(map, line, &is_coords, ++lines_readed))
			return (close(fd), free(line), 1);
		free(line);
		line = get_next_line(fd);
	}
	if (map->h < 3 || map->w < 3)
		return (close(fd), ft_putendl_fd(BAD_MAP_DIMS, 2), 1);
	if (map->player->view == '\0')
		return (close(fd), ft_putendl_fd(NO_PLAYER, 2), 1);
	return (close(fd), get_map_coords(map, file));
}
