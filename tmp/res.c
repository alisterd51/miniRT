/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   res.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 12:44:16 by anclarma          #+#    #+#             */
/*   Updated: 2020/10/25 18:13:47 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "exit_err.h"
#include "libft.h"
#include "read_line.h"

void	init_res(char *line, t_obj *obj)
{
	if (obj->res)
		return (exit_errcode(TO_MANY_RES_DECLARATION));
	if (!(obj->res = (t_res *)malloc(sizeof(t_res))))
		return (exit_errcode(MALLOC_ERROR));
	while (ft_isspace(*line))
		line++;
	obj->res->x_size = read_line_to_int(&line);
	while (ft_isspace(*line))
		line++;
	obj->res->y_size = read_line_to_int(&line);
	while (ft_isspace(*line))
		line++;
	if (*line)
		return (exit_errcode(RES_ERROR_LINE));
}

void	free_res(t_obj *obj)
{
	free(obj->res);
	obj->res = NULL;
}