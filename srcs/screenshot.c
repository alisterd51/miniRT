/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/15 21:39:06 by anclarma          #+#    #+#             */
/*   Updated: 2020/08/17 14:36:44 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "render.h"
#include "ft_tobmp.h"
#include <mlx.h>

void	ft_screenshot(t_mlx *mlx)
{
	oversampling(mlx);
    mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
	ft_tobmp(mlx, "test.bmp");
}