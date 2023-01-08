/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 00:40:27 by hyanagim          #+#    #+#             */
/*   Updated: 2023/01/09 02:32:03 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	look_mutex(t_philo *philo, t_vars *vars, t_status type)
{
	if (type == EATING_E)
	{
		pthread_mutex_lock(&philo->left->mtx);
		pthread_mutex_lock(&philo->right->mtx);
	}
	pthread_mutex_lock(&vars->mtx_stop);
	pthread_mutex_lock(&vars->mtx_write);
}

void	unlook_mutex(t_philo *philo, t_vars *vars, t_status type)
{
	if (type == EATING_E)
	{
		pthread_mutex_unlock(&philo->left->mtx);
		pthread_mutex_unlock(&philo->right->mtx);
	}
	pthread_mutex_unlock(&vars->mtx_stop);
	pthread_mutex_unlock(&vars->mtx_write);
}

void	destroy_mutexes(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->args.num_of_philos)
	{
		pthread_mutex_destroy(&vars->forks[i].mtx);
		i++;
	}
	pthread_mutex_destroy(&vars->mtx_stop);
}
