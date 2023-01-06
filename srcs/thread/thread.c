/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 23:45:36 by hyanagim          #+#    #+#             */
/*   Updated: 2023/01/06 17:39:06 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_philos_threads(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->args.num_of_philos)
	{
		pthread_create(&vars->philos[i].thread, NULL, philo_act, &vars->philos[i]);
		i++;
	}
}

void	create_monitor_thread(t_vars *vars)
{
	pthread_create(&vars->monitor.thread, NULL, monitor_act, &vars->monitor);
	pthread_mutex_init(&vars->monitor.alive, NULL);
}

void	join_threads(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->args.num_of_philos)
	{
		pthread_join(vars->philos[i].thread, NULL);
		i++;
	}
	pthread_join(vars->monitor.thread, NULL);
}

void	destroy_mutexes(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->args.num_of_philos)
	{
		pthread_mutex_destroy(&vars->forks[i].mutex);
		i++;
	}
	pthread_mutex_destroy(&vars->monitor.alive);
}
