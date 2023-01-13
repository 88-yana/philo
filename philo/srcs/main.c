/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 15:23:24 by hyanagim          #+#    #+#             */
/*   Updated: 2023/01/14 07:14:16 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "string.h"

void	create_threads(t_vars *vars)
{
	int		i;

	i = 0;
	while (i < vars->args.num_of_philos)
	{
		pthread_create(&vars->philos[i].thd, NULL, philo_act, &vars->philos[i]);
		i++;
	}
	pthread_create(&vars->monitor, NULL, monitor_act, vars);
}

void	join_threads(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->args.num_of_philos)
	{
		pthread_join(vars->philos[i].thd, NULL);
		i++;
	}
	pthread_join(vars->monitor, NULL);
}

void	destroy_mutexes(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->args.num_of_philos)
	{
		pthread_mutex_destroy(&vars->mtx_forks[i]);
		i++;
	}
	pthread_mutex_destroy(&vars->mtx_stop);
	pthread_mutex_destroy(&vars->mtx_time);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (check_args(argc, argv) == false)
		return (1);
	init_vars(&vars, argc, argv);
	create_threads(&vars);
	join_threads(&vars);
	destroy_mutexes(&vars);
	return (0);
}
