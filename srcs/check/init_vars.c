/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 18:50:55 by hyanagim          #+#    #+#             */
/*   Updated: 2023/01/04 19:09:17 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_args(t_vars *vars, int argc, char **argv)
{
	vars->args.time_to_die = ft_atoi(argv[2]);
	vars->args.time_to_eat = ft_atoi(argv[3]);
	vars->args.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		vars->args.times_to_eat_pasta = ft_atoi(argv[5]);
	else
		vars->args.times_to_eat_pasta = INT_MAX;
}

void	init_vars(t_vars *vars, int argc, char **argv)
{
	init_args(vars, argc, argv);
}
