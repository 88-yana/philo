/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 00:48:27 by hyanagim          #+#    #+#             */
/*   Updated: 2023/01/14 07:24:44 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_dead(int timestamp, t_philo *philo, t_vars *vars)
{
	pthread_mutex_lock(&vars->mtx_time);
	if (timestamp - philo->last_eat_time > vars->args.time_to_die)
	{
		pthread_mutex_unlock(&vars->mtx_time);
		return (true);
	}
	pthread_mutex_unlock(&vars->mtx_time);
	return (false);
}
