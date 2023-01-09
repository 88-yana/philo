/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:39:49 by hyanagim          #+#    #+#             */
/*   Updated: 2023/01/09 22:39:17 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	eating(t_philo *philo)
{
	bool	go_on;
	int		timestamp;

	go_on = true;
	lock_mutex(philo, philo->vars, EATING_E);
	timestamp = get_timestamp(philo->vars->start_time);
	lock_mutex(NULL, philo->vars, NONE);
	go_on = log_manager(timestamp, philo, philo->vars, EATING_E);
	unlock_mutex(NULL, philo->vars, NONE);
	if (go_on)
	{
		pthread_mutex_lock(&philo->vars->mtx_time);
		philo->last_eat_time = timestamp;
		philo->max_eat--;
		pthread_mutex_unlock(&philo->vars->mtx_time);
		stop_while_eating(timestamp, philo, philo->vars->args.time_to_eat);
	}
	unlock_mutex(philo, philo->vars, EATING_E);
	philo->status = SLEEPING_E;
	return (go_on);
}

static bool	sleeping(t_philo *philo)
{
	bool	go_on;
	int		timestamp;

	go_on = true;
	lock_mutex(NULL, philo->vars, NONE);
	timestamp = get_timestamp(philo->vars->start_time);
	go_on = log_manager(timestamp, philo, philo->vars, SLEEPING_E);
	unlock_mutex(NULL, philo->vars, NONE);
	if (go_on)
		stop_while_eating(timestamp, philo, philo->vars->args.time_to_sleep);
	philo->status = THINKING_E;
	return (go_on);
}

static bool	thinking(t_philo *philo)
{
	bool	go_on;
	int		timestamp;

	go_on = true;
	lock_mutex(NULL, philo->vars, NONE);
	timestamp = get_timestamp(philo->vars->start_time);
	go_on = log_manager(timestamp, philo, philo->vars, THINKING_E);
	unlock_mutex(NULL, philo->vars, NONE);
	philo->status = EATING_E;
	return (go_on);
}

void	*philo_act(void *arg)
{
	t_philo	*philo;
	bool	go_on;
	int		timestamp;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(100);
	if (philo->left == philo->right)
	{
		timestamp = get_timestamp(philo->vars->start_time);
		printf("%d %d %s\n", timestamp, philo->id, TAKEN_A_FORK_STR);
		return (NULL);
	}
	go_on = true;
	while (go_on && can_eat(philo))
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
