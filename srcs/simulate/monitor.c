/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 00:41:07 by hyanagim          #+#    #+#             */
/*   Updated: 2023/01/09 05:21:33 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	find_death(t_vars *vars, t_philo *philo)
{
	int	timestamp;

	timestamp = get_timestamp(vars->start_time);
	if (timestamp - philo->last_eat_time > vars->args.time_to_die)
	{
		vars->stop = true;
		pthread_mutex_lock(&vars->mtx_write);
		printf("%d %d %s\n", timestamp, philo->id, DIED_STR);//lock必要？
		pthread_mutex_unlock(&vars->mtx_write);
		return (true);
	}
	return (false);
}

static bool	death_detector(t_vars *vars)
{
	int		i;
	bool	go_on;

	go_on = true;
	i = 0;
	while (i < vars->args.num_of_philos)
	{
		pthread_mutex_lock(&vars->mtx_stop);
		if (vars->stop || find_death(vars, &vars->philos[i]))
		{
			go_on = false;
			pthread_mutex_unlock(&vars->mtx_stop);
			return (false);
		}
		pthread_mutex_unlock(&vars->mtx_stop);
		i++;
	}
	return (true);
}

void	*monitor_act(void *arg)
{
	t_vars	*vars;

	vars = (t_vars *)arg;
	while (death_detector(vars))
		;
	return (NULL);
}
