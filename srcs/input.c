/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 09:45:20 by anclarma          #+#    #+#             */
/*   Updated: 2020/07/24 11:29:18 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "render.h"
#include "input.h"
#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <mlx.h>
#include <math.h>

#include "libft.h"

int		deal_mouse(int button, int x, int y, t_mlx *mlx)
{
	char	chaine[100];

	sprintf(chaine, "button%d, x:%d, y:%d\n", button, x, y);
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, x, y, 0X00FFFFFF, chaine);
	return (0);
}

void	thisiskey1(int key, t_mlx *mlx)
{
	if (key == R_KEY)
		render(mlx);
	if (key == UP_KEY)
	{
		mlx->obj.lst_cam->c.z -= 2;
		prerender(mlx);
	}
	if (key == DOWN_KEY)
	{
		mlx->obj.lst_cam->c.z += 2;
		prerender(mlx);
	}
	if (key == S_KEY)
	{
		mlx->obj.lst_cam->c.y -= 2;
		prerender(mlx);
	}
	if (key == Z_KEY)
	{
		mlx->obj.lst_cam->c.y += 2;
		prerender(mlx);
	}
}

void	thisiskey2(int key, t_mlx *mlx)
{
	if (key == LEFT_KEY)
	{
		mlx->obj.lst_cam->c.x -= 2;
		prerender(mlx);
	}
	if (key == RIGHT_KEY)
	{
		mlx->obj.lst_cam->c.x += 2;
		prerender(mlx);
	}
	if (key == Q_KEY)
	{
		mlx->obj.lst_cam->vec = rot_right(mlx->obj.lst_cam->vec, M_PI / 128);
		//mlx->obj.lst_cam->vec.x -= 2;
		prerender(mlx);
	}
	if (key == D_KEY)
	{
		mlx->obj.lst_cam->vec = rot_left(mlx->obj.lst_cam->vec, M_PI / 4);
		//mlx->obj.lst_cam->vec.x += 2;
		prerender(mlx);
	}
	if (key == ESC_KEY)
		exit(0);
}

int		deal_key(int key, t_mlx *mlx)
{
	ft_printf("entree deal_key num: %d\n", key);
	thisiskey1(key, mlx);
	thisiskey2(key, mlx);
	return (0);
}
