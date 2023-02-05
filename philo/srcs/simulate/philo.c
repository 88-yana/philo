/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:39:49 by hyanagim          #+#    #+#             */
/*   Updated: 2023/02/05 10:25:39 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	eating(t_philo *philo)
{
	bool	go_on;
	int		timestamp;

	go_on = true;
	pthread_mutex_lock(philo->left);
	timestamp = get_timestamp(philo->vars->start_time);
	log_manager(timestamp, philo, philo->vars, TAKEN_A_FORK_STR);
	pthread_mutex_lock(philo->right);
	timestamp = get_timestamp(philo->vars->start_time);
	log_manager(timestamp, philo, philo->vars, TAKEN_A_FORK_STR);
	go_on = log_manager(timestamp, philo, philo->vars, EATING_STR);
	if (go_on)
	{
		pthread_mutex_lock(&philo->mtx_time);
		philo->last_eat_time = timestamp;
		pthread_mutex_unlock(&philo->mtx_time);
		stop_while_doing(timestamp, philo, philo->vars->args.time_to_eat);
		pthread_mutex_lock(&philo->mtx_time);
		philo->times_to_eat++;
		pthread_mutex_unlock(&philo->mtx_time);
	}
	pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(philo->left);
	return (go_on);
}

static bool	sleeping(t_philo *philo)
{
	bool	go_on;
	int		timestamp;

	go_on = true;
	timestamp = get_timestamp(philo->vars->start_time);
	go_on = log_manager(timestamp, philo, philo->vars, SLEEPING_STR);
	if (go_on)
		stop_while_doing(timestamp, philo, philo->vars->args.time_to_sleep);
	return (go_on);
}

static bool	thinking(t_philo *philo)
{
	bool	go_on;
	int		timestamp;

	go_on = true;
	timestamp = get_timestamp(philo->vars->start_time);
	go_on = log_manager(timestamp, philo, philo->vars, THINKING_STR);
	return (go_on);
}

void	*philo_act(void *arg)
{
	t_philo	*philo;
	bool	go_on;
	int		timestamp;

	philo = (t_philo *)arg;
	if (philo->left == philo->right)
	{
		timestamp = get_timestamp(philo->vars->start_time);
		printf("%d %d %s\n", timestamp, philo->id, TAKEN_A_FORK_STR);
		return (NULL);
	}
	if (philo->id % 2 == 0)
	{
		thinking(philo);
		usleep(100);
	}
	go_on = true;
	while (go_on)
	{
		go_on = eating(philo);
		go_on = sleeping(philo);
		go_on = thinking(philo);
	}
	return (NULL);
}
