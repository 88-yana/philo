/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:39:49 by hyanagim          #+#    #+#             */
/*   Updated: 2023/01/06 19:43:27 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	eating(t_philo *philo)
{
	int	go_on;

	go_on = true;
	pthread_mutex_look(philo->left);
	pthread_mutex_look(philo->right);
	pthread_mutex_look(philo->vars->monitor.alive);
	time_manager();
	if (death_manager())
	{
		write_action();
		go_on = false;
	}
	else if (cnt_eat_manager())
	{
		go_on = false;
	}
	else
		write_action();
	pthread_mutex_unlook(philo->left);
	pthread_mutex_unlook(philo->right);
	return (go_on);
}

static bool	sleeping(t_philo *philo)
{
	return (true);
}

static bool	thinking(t_philo *philo)
{
	return (true);
}

void	*philo_act(void *arg)
{
	t_philo	*philo;
	bool	go_on;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 1)
		usleep(100);
	go_on = true;
	while (go_on)
	{
		if (philo->state == EATING_E)
			go_on = eating(philo);
		else if (philo->state == SLEEPING_E)
			go_on = sleeping(philo);
		else if (philo->state == THINKING_E)
			go_on = thinking(philo);
	}
	return (NULL);
}
