/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scenescan.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 21:58:35 by anclarma          #+#    #+#             */
/*   Updated: 2021/03/13 10:53:29 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <math.h>
#include "struct.h"
#include "vector.h"
#include "getcolor.h"
#include "rot_vector.h"

static int	average_light(t_ray *ray, t_mlx *mlx)
{
	t_light		*light;
	t_vector	ret;
	double		denum;

	ret = (t_vector){0.0, 0.0, 0.0};
	denum = 0.0;
	light = mlx->obj->lst_light;
	while (light)
	{
		ret = add_vector(ret, getcolor(ray, mlx->obj, light, 20));
		denum += 1.0;
		light = light->next;
	}
	return (vector_to_int(div_vector(ret, denum)));
}

static void	*fonction(void *arg)
{
	t_arg	*a;
	t_mlx	*mlx;
	t_ray	ray;
	int		x;
	int		y;

	a = (t_arg*)arg;
	mlx = a->mlx;
	x = -1;
	while (++x < mlx->y_size)
	{
		y = a->y_min - 1;
		while (++y < a->y_max)
		{
			ray.coord = mlx->obj->current_cam->coord;
			ray.normal = rot_vector(mlx->obj->current_cam->rot,
				(t_vector){y - mlx->x_size / 2, x - mlx->y_size
				/ 2, -(mlx->x_size)
				/ (2 * tanf(mlx->obj->current_cam->fov_rad / 2))});
			ray.normal = normalize(ray.normal);
			mlx->image[(mlx->y_size - x - 1) * mlx->x_size + y] =
				average_light(&ray, mlx);
		}
	}
	return (NULL);
}

int			scenescan(t_mlx *mlx)
{
	pthread_t	thread[NB_THREADS];
	t_arg		arg[NB_THREADS];
	int			num_thread;

	num_thread = -1;
	while (++num_thread < NB_THREADS)
	{
		arg[num_thread].mlx = mlx;
		if (num_thread == 0)
			arg[num_thread].y_min = 0;
		else
			arg[num_thread].y_min = arg[num_thread - 1].y_max;
		arg[num_thread].y_max = mlx->x_size * (num_thread + 1) / NB_THREADS;
		if (pthread_create(&(thread[num_thread]), NULL, fonction,
				&(arg[num_thread])))
			return (1);
	}
	num_thread = -1;
	while (++num_thread < NB_THREADS)
		if (pthread_join(thread[num_thread], NULL))
			return (1);
	return (0);
}
