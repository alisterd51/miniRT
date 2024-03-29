/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getcolor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 14:50:28 by anclarma          #+#    #+#             */
/*   Updated: 2021/03/22 13:29:58 by pompier          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "struct.h"
#include "vector.h"
#include "getcolor.h"
#include "this_obj_is.h"
#include "check.h"
#include "extremum.h"
#include "intersect.h"
#include "albedo.h"
#include "add_amb_light.h"

static t_vector	ft_mirror(t_check *check, t_ray *ray, t_obj *obj, int nbrebonds)
{
	t_ray	ray_mirror;

	ray_mirror.normal = sub_vector(ray->normal,
		mult_vector(2.0 * dot(check->n, ray->normal), check->n));
	ray_mirror.coord = add_vector(check->p, mult_vector(0.001, check->n));
	return (getcolor(&ray_mirror, obj, check->light, nbrebonds));
}

static t_vector	ft_transp(t_check *check, t_ray *ray, t_obj *obj, int nbrebonds)
{
	t_ray		ray_refract;
	t_vector	n_transp;
	double		n1;
	double		n2;
	double		radical;

	n1 = 1.0;
	n2 = 1.3;
	n_transp = check->n;
	if (dot(ray->normal, check->n) > 0.0)
	{
		n1 = 1.3;
		n2 = 1.0;
		n_transp = mult_vector(-1.0, check->n);
	}
	radical = 1.0 - sqrt(n1 / n2) * (1.0 - sqrt(dot(n_transp, ray->normal)));
	if (radical <= 0.0)
		return ((t_vector){0.0, 0.0, 0.0});
	ray_refract.normal = sub_vector(mult_vector((n1 / n2),
		sub_vector(ray->normal, mult_vector(dot(ray->normal, n_transp),
		n_transp))), mult_vector(sqrt(radical), n_transp));
	ray_refract.coord = sub_vector(check->p, mult_vector(0.001, n_transp));
	return (getcolor(&ray_refract, obj, check->light, nbrebonds));
}

static int		side_shadow_camera(t_check *check, t_obj *obj)
{
	t_check		check_light;
	t_ray		ray_light;
	int			has_inter_light;
	double		d_light2;
	t_vector	obj_vers_cam;

	obj_vers_cam = normalize(sub_vector(obj->current_cam->coord, check->p));
	ray_light.coord = add_vector(check->p, mult_vector(0.001, obj_vers_cam));
	ray_light.normal = normalize(sub_vector(check->light->coord, check->p));
	check_light = init_check(&ray_light, obj, check->light);
	has_inter_light = rt_inter_scene(&check_light);
	d_light2 = norm2(sub_vector(check->light->coord, check->p));
	if (has_inter_light && check_light.t * check_light.t < d_light2)
		return (1);
	return (0);
}

static t_vector	ft_direct(t_check *check, t_obj *obj)
{
	t_check		check_light;
	t_ray		ray_light;
	int			has_inter_light;
	double		d_light2;

	if (side_shadow_camera(check, obj))
		return ((t_vector){0.0, 0.0, 0.0});
	ray_light.coord = add_vector(check->p, mult_vector(0.001, check->n));
	ray_light.normal = normalize(sub_vector(check->light->coord, check->p));
	check_light = init_check(&ray_light, obj, check->light);
	has_inter_light = rt_inter_scene(&check_light);
	d_light2 = norm2(sub_vector(check->light->coord, check->p));
	if (has_inter_light && check_light.t * check_light.t < d_light2)
		return ((t_vector){0.0, 0.0, 0.0});
	else
		return (div_vector(mult_vector(check->light->ratio
			* obj->intensite_lumiere * max(0.0,
			dot(normalize(sub_vector(check->light->coord, check->p)),
			check->n)), div_vector(color_lum(obj_albedo(check),
			check->light->color), M_PI)), d_light2));
}

t_vector		getcolor(t_ray *ray, t_obj *obj, t_light *light, int nbrebonds)
{
	t_vector	color;
	t_check		check;
	int			has_inter;

	color = (t_vector){0.0, 0.0, 0.0};
	if (nbrebonds == 0)
		return (color);
	check = init_check(ray, obj, light);
	has_inter = rt_inter_scene(&check);
	if (has_inter)
	{
		if (this_obj_is_mirror(&check))
			color = add_vector(mult_vector(0.01, ft_direct(&check, obj)),
				mult_vector(0.99, ft_mirror(&check, ray, obj, nbrebonds - 1)));
		else if (this_obj_is_transp(&check))
			color = ft_transp(&check, ray, obj, nbrebonds - 1);
		else
			color = ft_direct(&check, obj);
	}
	return (add_vector(color, add_amb_light(&check, obj)));
}
