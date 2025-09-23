/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_coords.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlossalazar <carlossalazar@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 14:09:49 by csalazar          #+#    #+#             */
/*   Updated: 2025/09/23 07:50:13 by carlossalaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cube3D.h"

/* void	valid_map(char **map, int x, int y)
{
	if (y < 0 || x < 0 || map[y][x] == '-' || map[y][x] == '1'
		|| map[y][x] == 'E')
		return ;
	map[y][x] = '-';
	valid_map(map, x + 1, y);
	valid_map(map, x - 1, y);
	valid_map(map, x, y + 1);
	valid_map(map, x, y - 1);
}

void	check_map(t_game *game)
{
	int	y;
	int	x;
	int	count_c;

	count_c = 0;
	valid_map(game->map.cp_full, game->map.player.x, game->map.player.y);
	y = 0;
	while (y < game->map.rows)
	{
		x = 0;
		while (x < game->map.columns)
		{
			if (game->map.cp_full[y][x] == 'C')
				count_c = 1;
			if (game->map.cp_full[y][x] == '0')
				ft_error_msg("IMPOSSIBLE MAP!!!", game);
			x++;
		}
		y++;
	}
	if (count_c == 1)
		ft_error_msg("IMPOSSIBLE MAP!!!", game);
	ft_free_cpmap(game);
}

static int verify_map_nav(t_map *map)
{

} */

static void flood_fill(t_map *map, int row, int col, int *i)
{
    if (row < 0  || row > (int)map->h - 2 || col < 0 || col > (int)ft_strlen(map->coords[row]) - 2)
        return ;
    if (map->coords[row][col] == '0' || ft_is_coord(map->coords[row][col]))
    {
        map->coords[row][col] = '-';
        (*i)++;
        flood_fill(map, row - 1, col, i);
        flood_fill(map, row + 1, col, i);
        flood_fill(map, row, col - 1, i);
        flood_fill(map, row, col + 1, i);
    }
}

static int verify_map_nav(t_map *map)
{
    int i;

    i= 0;

    flood_fill(map, map->player->row, map->player->col, &i);
    printf("Num spaces: %d, flood fill: %d\n", map->num_spaces, i);
    if (i < map->num_spaces)
        return (1);
    return (0);
}

static int verify_map_borders(t_map *map)
{
    size_t i;
    size_t j;

    i = 0;
    while (map->coords[i])
    {
        j = 0;
        while (map->coords[i][j])
        {
            if (map->coords[i][j] == '0' || ft_is_coord(map->coords[i][j]))
            {
                if (i == 0 || i == map->h - 1)
                    return (1);
                if (j == 0 || j == ft_strlen(map->coords[i]) - 2)
                    return (1);
                if (j >= ft_strlen(map->coords[i - 1]) - 1 || j >= ft_strlen(map->coords[i + 1]) - 1)
                    return (1);
                if (map->coords[i][j - 1] == ' ' || map->coords[i][j + 1] == ' ' || map->coords[i - 1][j] == ' ' || map->coords[i + 1][j] == ' ')
                    return (1);
            }
            j++;
        }
        i++;
    }
    return (0);
}

static void copy_map_coords(t_map *map, int fd)
{
    char *line;
    int f;

    line = get_next_line(fd);
    f = 0;
    while (line)
    {
        map->coords[f++] = ft_strdup(line);
        free(line);
        line = get_next_line(fd);
    }
    map->coords[f] = NULL;
}

int get_map_coords(t_map *map, char *file)
{
    int fd;
    char *line;
    int lines_readed;
    
    lines_readed = 0;
    fd = open(file, O_RDONLY);
    if (fd == -1)
        return (ft_putendl_fd(ERR_OPEN_FILE, 2), 1);
    while (++lines_readed < map->coords_fl)
    {
        line = get_next_line(fd);
        free(line);
    }
    map->coords = malloc((map->h + 1) * sizeof(char *));
    if (!map->coords)
        return (ft_putendl_fd(ERR_MALLOC_DATA, 2), 1);
    copy_map_coords(map, fd);
    if (verify_map_borders(map))
        return (ft_putendl_fd(OPEN_MAP, 2), 1);
    if (verify_map_nav(map))
        return (ft_putendl_fd(ERR_NAV_MAP, 2), 1);
    return (close(fd), 0);
}
