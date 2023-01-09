/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 00:15:58 by hyanagim          #+#    #+#             */
/*   Updated: 2023/01/09 22:20:59 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	log_manager(int timestamp, t_philo *philo, t_vars *vars, t_status type)
{
	if (vars->stop)
		return (false);
	else if (is_dead(timestamp, philo->last_eat_time, vars->args.time_to_die))
	{
		vars->stop = true;
		usleep(5000);
		printf("%d %d %s\n", timestamp, philo->id, DIED_STR);
		return (false);
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
	return (true);
}
