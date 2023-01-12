/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 00:41:07 by hyanagim          #+#    #+#             */
/*   Updated: 2023/01/12 19:48:36 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	find_death(t_vars *vars, t_philo *philo) //go_on 使えば綺麗になる
{
	int	timestamp;

	timestamp = get_timestamp(vars->start_time);
	if (is_dead(timestamp, philo->last_eat_at, vars->args.time_die, vars))
	{
		vars->stop = true;
		pthread_mutex_unlock(&vars->mtx_stop);
		usleep(5000);
		pthread_mutex_lock(&vars->mtx_write);
		printf("%d %d %s\n", timestamp, philo->id, DIED_STR);
		pthread_mutex_unlock(&vars->mtx_write);
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
		pthread_mutex_lock(&vars->mtx_stop);
		if (vars->stop)
		{
			pthread_mutex_unlock(&vars->mtx_stop);
			return (false);
		}
		else if (find_death(vars, &vars->philos[i]))
			return (false);
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
