/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 00:41:07 by hyanagim          #+#    #+#             */
/*   Updated: 2023/01/14 06:59:00 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	find_death(t_vars *vars, t_philo *philo) //go_on 使えば綺麗になる
{
	int	timestamp;

	pthread_mutex_lock(&vars->mtx_stop);
	timestamp = get_timestamp(vars->start_time);
	if (is_dead(timestamp, philo, vars))
	{
		vars->stop = true;
		printf("%d %d %s\n", timestamp, philo->id, DIED_STR);
		pthread_mutex_unlock(&vars->mtx_stop);
		return (true);
	}
	pthread_mutex_unlock(&vars->mtx_stop);
	return (false);
}

void	*monitor_act(void *arg)
{
	t_vars	*vars;
	int		i;
	bool	all_philos_over_must_eat;

	vars = (t_vars *)arg;
	i = 0;
	while (1)
	{
		if (i == 0)
			all_philos_over_must_eat = true;
		if (find_death(vars, &vars->philos[i]))
			break ;
		pthread_mutex_lock(&vars->mtx_time);
		if (vars->philos[i].times_to_eat < vars->args.times_must_eat)
			all_philos_over_must_eat = false;
		pthread_mutex_unlock(&vars->mtx_time);
		i = (i + 1) % vars->args.num_of_philos;
		if (i == 0 && all_philos_over_must_eat)
			break ;
	}
	pthread_mutex_lock(&vars->mtx_stop);
	vars->stop = true;
	pthread_mutex_unlock(&vars->mtx_stop);
	return (NULL);
}
