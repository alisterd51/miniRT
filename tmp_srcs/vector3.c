/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 19:15:58 by anclarma          #+#    #+#             */
/*   Updated: 2021/01/09 11:28:58 by anclarma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "extremum.h"
#include "vector.h"
#include <math.h>

t_vector	int_to_vector(int color)
{
	t_vector	new_vec;

	new_vec.x = color % 256;
	color /= 256;
	new_vec.y = color % 256;
	color /= 256;
	new_vec.z = color % 256;
	return (new_vec);
}

int			vector_to_int(t_vector vec)
{
	int	ret;

	ret = (int)max(0.0, min(255.0, pow(vec.x, 1 / 2.2)))
		+ (int)max(0.0, min(255.0, pow(vec.y, 1 / 2.2))) * 256
		+ (int)max(0.0, min(255.0, pow(vec.z, 1 / 2.2))) * 256 * 256;
	return (ret);
}

int			vector_to_ints(t_vector vec)
{
	int	ret;

	ret = (int)max(0.0, min(255.0, vec.x))
		+ (int)max(0.0, min(255.0, vec.y)) * 256
		+ (int)max(0.0, min(255.0, vec.z)) * 256 * 256;
	return (ret);
}

t_vector	color_to_vector(t_color color)
{
	t_vector	ret;

	ret.x = (double)((unsigned char)color.r);
	ret.y = (double)((unsigned char)color.g);
	ret.z = (double)((unsigned char)color.b);
	return (ret);
}
