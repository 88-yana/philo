/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:39:49 by hyanagim          #+#    #+#             */
/*   Updated: 2023/01/08 22:58:13 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	eating(t_philo *philo)
{
	int		go_on;
	int		timestamp;
	t_vars	*vars;

	if (philo->left == philo->right)
	{
		write_action(timestamp, philo->id, TAKEN_A_FORK_STR);
		return (false);
	}
	vars = philo->vars;
	go_on = true;
	// if (philo->left == philo->right) //philoが一人のとき
	pthread_mutex_look(philo->left);
	pthread_mutex_look(philo->right);
	pthread_mutex_look(&vars->monitor.mtx_stop);
	pthread_mutex_look(&vars->write);
	timestamp = get_timestamp();
	if (vars->stop)
		go_on = false;
	else if (is_dead(vars->args.time_to_die, timestamp))
	{
		vars->stop = true;
		write_action(timestamp, philo->id, DIED_STR);
		go_on = false;
	}
	// else if (cnt_eat_manager()) //どっかのphiloがmaxのeatに達していたら，というif文が必要なのか？
	// {
	// 	go_on = false;
	// }
	else
	{
		write_action(timestamp, philo->id, TAKEN_A_FORK_STR);
		write_action(timestamp, philo->id, TAKEN_A_FORK_STR);
		write_action(timestamp, philo->id, EATING_STR);
	}
	pthread_mutex_unlook(&vars->write);
	pthread_mutex_unlook(&vars->monitor.mtx_stop);
	pthread_mutex_unlook(philo->left);
	pthread_mutex_unlook(philo->right);
	stop_while_eating(vars->start_time + timestamp + vars->args.time_to_eat);
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
	while (go_on && can_eat(philo))
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
