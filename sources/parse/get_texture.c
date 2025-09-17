/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csalazar <csalazar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 12:52:59 by csalazar          #+#    #+#             */
/*   Updated: 2025/09/02 17:22:22 by csalazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Cube3D.h"

int get_texture_from_line(char *line, int i, char **texture)
{
    if (*texture)
        return (ft_putendl_fd(DUP_TEXTURE_FILE, 2), 1);
    while (line[i] && ft_isspace(line[i]))
        i++;
    if (!line[i])
        return (ft_putendl_fd(NOT_TEXTURE_FILE_SPEC, 2), 1);
    *texture = ft_strdup(&line[i]);
    if ((*texture)[ft_strlen(*texture) - 1] == '\n')
        (*texture)[ft_strlen(*texture) - 1] = '\0';
    return (0);
}
