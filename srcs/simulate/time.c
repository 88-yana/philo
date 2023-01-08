/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 01:32:57 by hyanagim          #+#    #+#             */
/*   Updated: 2023/01/09 02:31:26 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_timestamp(int start_time)
{
	int				timestamp;
	struct timeval	now_time;

	gettimeofday(&now_time, NULL);
	timestamp = 1000 * now_time.tv_sec + now_time.tv_usec / 1000 - start_time;
	return (timestamp);
}

void	stop_while_eating(int timestamp, t_philo *philo, int time_to_do)
{
	int	until_time;

	until_time = timestamp + time_to_do;
	while (get_timestamp(philo->vars->start_time) < until_time)
		usleep(100);
}
