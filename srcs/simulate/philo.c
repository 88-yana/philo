/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:39:49 by hyanagim          #+#    #+#             */
/*   Updated: 2023/01/09 04:26:19 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	eating(t_philo *philo)
{
	bool	go_on;
	int		timestamp;

	if (philo->left == philo->right)
	{
		timestamp = get_timestamp(philo->vars->start_time);
		printf("%d %d %s\n", timestamp, philo->id, TAKEN_A_FORK_STR);
		return (false);
	}
	go_on = true;
	look_mutex(philo, philo->vars, EATING_E);
	timestamp = get_timestamp(philo->vars->start_time);
	go_on = log_manager(timestamp, philo, philo->vars, EATING_E);
	unlook_mutex(philo, philo->vars, NONE);
	if (go_on)
	{
		philo->last_eat_time = timestamp;
		philo->times_to_eat_pasta--;
		stop_while_eating(timestamp, philo, philo->vars->args.time_to_eat);
	}
	unlook_mutex(philo, philo->vars, EATING_E);
	philo->status = SLEEPING_E;
	return (go_on);
}

static bool	sleeping(t_philo *philo)
{
	bool	go_on;
	int		timestamp;

	go_on = true;
	look_mutex(philo, philo->vars, NONE);
	timestamp = get_timestamp(philo->vars->start_time);
	go_on = log_manager(timestamp, philo, philo->vars, SLEEPING_E);
	unlook_mutex(philo, philo->vars, NONE);
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
	look_mutex(philo, philo->vars, NONE);
	timestamp = get_timestamp(philo->vars->start_time);
	go_on = log_manager(timestamp, philo, philo->vars, THINKING_E);
	unlook_mutex(philo, philo->vars, NONE);
	philo->status = EATING_E;
	return (go_on);
}

void	*philo_act(void *arg)
{
	t_philo	*philo;
	bool	go_on;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(100);
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
