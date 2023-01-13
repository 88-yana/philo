/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 00:15:58 by hyanagim          #+#    #+#             */
/*   Updated: 2023/01/14 06:46:00 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	log_manager(int timestamp, t_philo *philo, t_vars *vars, t_status type)
{
	bool	go_on;

	go_on = true;
	lock_mutex(NULL, philo->vars, STOP_WRITE);
	if (vars->stop)
		go_on = false;
	else if (is_dead(timestamp, philo, vars))
	{
		vars->stop = true;
		printf("%d %d %s\n", timestamp, philo->id, DIED_STR);
		go_on = false;
	}
	else if (type == EATING_E)
	{
		printf("%d %d %s\n", timestamp, philo->id, TAKEN_A_FORK_STR);
		printf("%d %d %s\n", timestamp, philo->id, TAKEN_A_FORK_STR);
		printf("%d %d %s\n", timestamp, philo->id, EATING_STR);
	}
	else if (type == SLEEPING_E)
		printf("%d %d %s\n", timestamp, philo->id, SLEEPING_STR);
	else if (type == THINKING_E)
		printf("%d %d %s\n", timestamp, philo->id, THINKING_STR);
	unlock_mutex(NULL, philo->vars, STOP_WRITE);
	return (go_on);
}
