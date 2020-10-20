/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 17:06:45 by anclarma          #+#    #+#             */
/*   Updated: 2020/10/20 15:45:26 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "lst_obj.h"

static void	parse_line(char *line, t_obj *obj)
{
	if (!line || !*line)
		return exit_errcode(ERROR_LINE);
	else if (*line == '#')
		return ;
	else if (!*(line + 1))
		return exit_errcode(ERROR_LINE);
	else if (*line == 'R' && ft_isspace(*(line + 1)))
		init_res(line + 1, obj);
	else if (*line == 'A' && ft_isspace(*(line + 1)))
		init_amb_light(line + 1, obj);
	else if (*line == 'c' && ft_isspace(*(line + 1)))
		init_lst_cam(line + 1, obj);
	else if (*line == 'l' && ft_isspace(*(line + 1)))
		init_lst_light(line + 1, obj);
	else if (!*(line + 2))
		return exit_errcode(ERROR_LINE);
	else if (*line == 's' && *(line + 1) == 'p' && ft_isspace(*(line + 2)))
		init_lst_sphere(line + 1, obj);
	else if (*line == 'p' && *(line + 1) == 'l' && ft_isspace(*(line + 2)))
		init_lst_plane(line + 1, obj);
	else if (*line == 's' && *(line + 1) == 'q' && ft_isspace(*(line + 2)))
		init_lst_square(line + 1, obj);
	else if (*line == 'c' && *(line + 1) == 'y' && ft_isspace(*(line + 2)))
		init_lst_cylinder(line + 1, obj);
	else if (*line == 't' && *(line + 1) == 'r' && ft_isspace(*(line + 2)))
		init_lst_triangle(line + 1, obj);
	else if (*line == 'c' && *(line + 1) == 'u' && ft_isspace(*(line + 2)))
		init_lst_cube(line + 1, obj);
	else if (*line == 'p' && *(line + 1) == 'y' && ft_isspace(*(line + 2)))
		init_lst_pyramid(line + 1, obj);
	else if (*line == 'c' && *(line + 1) == 'o' && ft_isspace(*(line + 2)))
		init_lst_cone(line + 1, obj);
	else
		return exit_errcode(UNRECOGNIZED_LINE);
}

void		parsing(char *param, t_obj *obj)
{
	int		fd;
	int		ret_gnl;
	char	*line;

	if (check_file_rt(param))
		return (exit_errcode(NOT_RT_FILE));
	if ((fd = open(param, O_RDONLY)) == -1)
		return (exit_errcode(OPEN_ERROR));
	while ((ret_gnl = get_next_line(fd, &line)) == 1)
	{
		parse_line(line, obj);
		free(line);
	}
	if (ret_gnl == -1)
		return (exit_errcode(GNL_ERROR));
	parse_line(line, obj);
	free(line);
	if (close(fd))
		return (exit_errcode(CLOSE_ERROR));
}
