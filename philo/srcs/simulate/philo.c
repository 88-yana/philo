/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:39:49 by hyanagim          #+#    #+#             */
/*   Updated: 2023/01/14 08:13:47 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	eating(t_philo *philo)
{
	bool	go_on;
	int		timestamp;

	go_on = true;
	pthread_mutex_lock(philo->left);
	pthread_mutex_lock(philo->right);
	timestamp = get_timestamp(philo->vars->start_time);
	go_on = log_manager(timestamp, philo, philo->vars, EATING_E);
	if (go_on)
	{
		pthread_mutex_lock(&philo->vars->mtx_time);
		philo->last_eat_time = timestamp;
		pthread_mutex_unlock(&philo->vars->mtx_time);
		stop_while_doing(timestamp, philo, philo->vars->args.time_to_eat);
		pthread_mutex_lock(&philo->vars->mtx_time);
		philo->times_to_eat++;
		pthread_mutex_unlock(&philo->vars->mtx_time);
	}
	pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(philo->left);
	philo->status = SLEEPING_E;
	return (go_on);
}

static bool	sleeping(t_philo *philo)
{
	bool	go_on;
	int		timestamp;

	go_on = true;
	timestamp = get_timestamp(philo->vars->start_time);
	go_on = log_manager(timestamp, philo, philo->vars, SLEEPING_E);
	if (go_on)
		stop_while_doing(timestamp, philo, philo->vars->args.time_to_sleep);
	philo->status = THINKING_E;
	return (go_on);
}

static bool	thinking(t_philo *philo)
{
	bool	go_on;
	int		timestamp;

	go_on = true;
	timestamp = get_timestamp(philo->vars->start_time);
	go_on = log_manager(timestamp, philo, philo->vars, THINKING_E);
	philo->status = EATING_E;
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
		usleep(100);
	go_on = true;
	while (go_on)
	{
		if (philo->status == EATING_E)
			go_on = eating(philo);
		else if (philo->status == SLEEPING_E)
			go_on = sleeping(philo);
		else if (philo->status == THINKING_E)
			go_on = thinking(philo);
	}
	return (NULL);
}
