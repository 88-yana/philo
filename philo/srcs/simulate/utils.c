/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 00:15:58 by hyanagim          #+#    #+#             */
/*   Updated: 2023/02/23 16:45:21 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	log_manager(t_philo *philo, t_vars *vars, char *type)
{
	bool	go_on;
	int		timestamp;

	go_on = true;
	pthread_mutex_lock(&vars->mtx_stop);
	timestamp = get_timestamp(philo->vars->start_time);
	if (vars->stop)
		go_on = false;
	else if (is_dead(timestamp, philo, vars))
	{
		vars->stop = true;
		printf("%d %d %s\n", timestamp, philo->id, DIED_STR);
		go_on = false;
	}
	else if (type == EATING_STR)
		printf("%d %d %s\n", timestamp, philo->id, EATING_STR);
	else if (type == TAKEN_A_FORK_STR)
		printf("%d %d %s\n", timestamp, philo->id, TAKEN_A_FORK_STR);
	else
		printf("%d %d %s\n", timestamp, philo->id, type);
	pthread_mutex_unlock(&vars->mtx_stop);
	return (go_on);
}

int	get_timestamp(int start_time)
{
	int				timestamp;
	struct timeval	now_time;

	gettimeofday(&now_time, NULL);
	timestamp = 1000 * now_time.tv_sec + now_time.tv_usec / 1000 - start_time;
	return (timestamp);
}

void	stop_while_doing(int timestamp, t_philo *philo, int time_to_do)
{
	int	until_time;

	until_time = timestamp + time_to_do;
	usleep(time_to_do - 200);
	while (get_timestamp(philo->vars->start_time) < until_time)
		usleep(100);
}

bool	is_dead(int timestamp, t_philo *philo, t_vars *vars)
{
	pthread_mutex_lock(&philo->mtx_time);
	if (timestamp - philo->last_eat_time > vars->args.time_to_die)
	{
		pthread_mutex_unlock(&philo->mtx_time);
		return (true);
	}
	pthread_mutex_unlock(&philo->mtx_time);
	return (false);
}
