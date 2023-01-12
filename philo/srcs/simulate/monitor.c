/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 00:41:07 by hyanagim          #+#    #+#             */
/*   Updated: 2023/01/13 00:23:36 by hyanagim         ###   ########.fr       */
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
		pthread_mutex_lock(&vars->mtx_write);
		printf("%d %d %s\n", timestamp, philo->id, DIED_STR);
		pthread_mutex_unlock(&vars->mtx_write);
		return (true);
	}
	return (false);
}

static bool	death_detector(t_vars *vars)
{
	int		i;
	bool	all_philos_over_eat;

	all_philos_over_eat = true;
	i = 0;
	while (i < vars->args.num_of_philos) //TODO:break とか使えば，mutexが綺麗になるかも
	{
		pthread_mutex_lock(&vars->mtx_stop);
		if (vars->stop)
		{
			pthread_mutex_unlock(&vars->mtx_stop);
			return (false);
		}
		else if (find_death(vars, &vars->philos[i]))
			return (false);
		pthread_mutex_lock(&vars->mtx_time);
		if (vars->philos[i].times_to_eat < vars->args.times_must_eat)
			all_philos_over_eat = false;
		pthread_mutex_lock(&vars->mtx_time);
		pthread_mutex_unlock(&vars->mtx_stop);
		i++;
	}
	if (all_philos_over_eat)
	{
		pthread_mutex_lock(&vars->mtx_stop);
		vars->stop = true;
		pthread_mutex_unlock(&vars->mtx_stop);
		return (false);
	}
	return (true);
}

void	*monitor_act(void *arg)
{
	t_vars	*vars;
	int		i;

	vars = (t_vars *)arg;
	i = 0;
	while (1)
	{
		pthread_mutex_lock(&vars->mtx_stop);
		if (find_death(vars, &vars->philos[i]))
			break ;
		else if (is_all_have_eaten())
			break ;
		i = (i + 1) % vars->args.num_of_philos;
	}
	return (NULL);
}
