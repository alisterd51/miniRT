/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 15:43:51 by anclarma          #+#    #+#             */
/*   Updated: 2021/01/09 20:58:01 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <mlx.h>
#include "lst_obj.h"
#include "parsing.h"
#include "exit_err.h"
#include "input.h"

#include "tmp_lst_obj.h"

static t_mlx	*init_mlx(t_obj *obj)
{
	t_mlx	*mlx;
	int		i;

	mlx = (t_mlx *)malloc(sizeof(t_mlx));
	if (!mlx)
		exit_errcode(MALLOC_ERROR);
	mlx->x_size = obj->res->x_size;//si x_size > x_size_max alors x_size = x_size_max
	mlx->y_size = obj->res->y_size;//si y_size > y_size_max alors y_size = y_size_max
	mlx->mlx_ptr = mlx_init();
	mlx->size_line = obj->res->x_size * 4;
	mlx->bpp = 32;
	mlx->endian = 1;
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, mlx->x_size, mlx->y_size);
	mlx->image = (int *)mlx_get_data_addr(mlx->img_ptr,
			&(mlx->bpp), &(mlx->size_line), &(mlx->endian));
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, mlx->x_size,
			mlx->y_size, "Test");
	mlx->aa = 8;
	mlx->iaa = 16;
	mlx->nb_thread = 8;
	obj->intensite_lumiere = 2000000;
	mlx->pixel = (int **)malloc(sizeof(int *) * mlx->y_size);
	i = -1;
	while (++i < mlx->y_size)
		mlx->pixel[i] = (int *)malloc(sizeof(int) * mlx->x_size);
	mlx->obj = obj;
	return (mlx);
}

int				main(int ac, char **av)
{
	t_obj	*obj;
	t_mlx	*mlx;

	obj = init_obj();
	if (!obj)
		exit_errcode(MALLOC_ERROR);
	if (ac != 2)
	{
		exit_errcode(ARGC_ERROR);
		return (1);
	}
	parsing(av[1], obj);
//	print_obj(obj);
	mlx = init_mlx(obj);
	mlx_hook(mlx->win_ptr, 2, (1L << 0), ft_keypress, (void *)mlx);
	mlx_hook(mlx->win_ptr, 17, (1L << 17), exit_hook, (void *)0);
	mlx_loop(mlx->mlx_ptr);
	return (0);
}
