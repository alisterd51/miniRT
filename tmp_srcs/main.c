/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anclarma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 15:43:51 by anclarma          #+#    #+#             */
/*   Updated: 2020/11/27 17:12:02 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "lst_obj.h"
#include "parsing.h"
#include "exit_err.h"

#include <stdio.h>

int	main(int ac, char **av)
{
	t_obj	*obj;

	if (!(obj = init_obj()))
		exit_errcode(MALLOC_ERROR);
	if (ac != 2)
	{
		exit_errcode(ARGC_ERROR);
		return (1);
	}
	parsing(av[1], obj);
	print_obj(obj);
	free_obj(&obj);
	return (0);
}