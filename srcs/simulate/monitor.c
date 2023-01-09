/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 00:41:07 by hyanagim          #+#    #+#             */
/*   Updated: 2023/01/09 20:01:01 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	find_death(t_vars *vars, t_philo *philo)
{
	int	timestamp;
	int	time;

	if (vars->stop)
		return (true);
	(void) philo;
	timestamp = get_timestamp(vars->start_time);
	time = philo->last_eat_time;
	if (timestamp > vars->args.time_to_die + philo->last_eat_time)
	{
		if (vars->stop)
			return (true);
		vars->stop = true;
		usleep(5000);
		printf("%d %d %s\n", timestamp, philo->id, DIED_STR);//lock必要？
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
		pthread_mutex_lock(&vars->mtx_write);
		if (vars->stop || find_death(vars, &vars->philos[i]))
		{
			go_on = false;
			pthread_mutex_unlock(&vars->mtx_stop);
			pthread_mutex_unlock(&vars->mtx_write);
			return (false);
		}
		pthread_mutex_unlock(&vars->mtx_stop);
		pthread_mutex_unlock(&vars->mtx_write);
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
