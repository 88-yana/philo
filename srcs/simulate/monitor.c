/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 00:41:07 by hyanagim          #+#    #+#             */
/*   Updated: 2023/01/09 22:40:42 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	find_death(t_vars *vars, t_philo *philo)
{
	int	timestamp;

	if (vars->stop)
		return (true);
	(void) philo;
	timestamp = get_timestamp(vars->start_time);
	pthread_mutex_lock(&philo->vars->mtx_time);
	if (timestamp > vars->args.time_to_die + philo->last_eat_time)
	{
		pthread_mutex_unlock(&philo->vars->mtx_time);
		if (vars->stop)
			return (true);
		vars->stop = true;
		usleep(5000);
		printf("%d %d %s\n", timestamp, philo->id, DIED_STR);
		return (true);
	}
	pthread_mutex_unlock(&philo->vars->mtx_time);
	return (false);
}

static bool	death_detector(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->args.num_of_philos)
	{
		lock_mutex(NULL, vars, NONE);
		if (vars->stop || find_death(vars, &vars->philos[i]))
		{
			unlock_mutex(NULL, vars, NONE);
			return (false);
		}
		unlock_mutex(NULL, vars, NONE);
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
