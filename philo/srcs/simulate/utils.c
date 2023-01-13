/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 00:48:27 by hyanagim          #+#    #+#             */
/*   Updated: 2023/01/14 06:40:22 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_dead(int timestamp, t_philo *philo, t_vars *vars)
{
	pthread_mutex_lock(&vars->mtx_time);
	if (timestamp - philo->last_eat_at> vars->args.time_die)
	{
		pthread_mutex_unlock(&vars->mtx_time);
		return (true);
	}
	pthread_mutex_unlock(&vars->mtx_time);
	return (false);
}

void	lock_mutex(t_philo *philo, t_vars *vars, t_status type)
{
	if (type == EATING_E)
	{
		pthread_mutex_lock(philo->left);
		pthread_mutex_lock(philo->right);
	}
	else
	{
		pthread_mutex_lock(&vars->mtx_stop);
		pthread_mutex_lock(&vars->mtx_write);
	}
}

void	unlock_mutex(t_philo *philo, t_vars *vars, t_status type)
{
	if (type == EATING_E)
	{
		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(philo->right);
	}
	else
	{
		pthread_mutex_unlock(&vars->mtx_stop);
		pthread_mutex_unlock(&vars->mtx_write);
	}
}
