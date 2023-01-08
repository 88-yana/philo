/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 23:45:36 by hyanagim          #+#    #+#             */
/*   Updated: 2023/01/09 04:22:13 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_philos_threads(t_vars *vars)
{
	int		i;

	i = 0;
	while (i < vars->args.num_of_philos)
	{
		pthread_create(&vars->philos[i].thd, NULL, philo_act, &vars->philos[i]);
		i++;
	}
}

// void	create_monitor_thread(t_vars *vars)
// {
// 	pthread_create(&vars->monitor.thread, NULL, monitor_act, &vars->monitor);
// }

void	join_threads(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->args.num_of_philos)
	{
		pthread_join(vars->philos[i].thd, NULL);
		i++;
	}
	pthread_join(vars->monitor.thread, NULL);
}