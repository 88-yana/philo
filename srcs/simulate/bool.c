/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 00:48:27 by hyanagim          #+#    #+#             */
/*   Updated: 2023/01/09 02:28:41 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_dead(int timestamp, int last_eat_time, int time_to_die)
{
	if (timestamp - last_eat_time > time_to_die)
		return (true);
	return (false);
}

bool	can_eat(t_philo *philo)
{
	if (philo->times_to_eat_pasta == 0)
		if (philo->status == EATING_E)
			return (false);
	return (true);
}
