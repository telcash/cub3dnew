/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carlossalazar <carlossalazar@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 11:28:39 by csalazar          #+#    #+#             */
/*   Updated: 2025/09/23 09:27:43 by carlossalaz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cube3D.h"

static int	check_file(char *f)
{
	size_t	l;

	l = ft_strlen(f);
	if (l < 5 || f[l - 4] != '.' || f[l - 3] != 'c' || f[l - 2] != 'u' || f[l
		- 1] != 'b')
		return (ft_putendl_fd(ERR_INV_FILE, 2), 1);
	return (0);
}

int	parse_map(t_map *map, char *file)
{
	if (!map)
		return (1);
	if (check_file(file))
		return (1);
	if (get_map_data(map, file))
		return (1);
	return (0);
}
