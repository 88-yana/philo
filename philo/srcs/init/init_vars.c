/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 18:50:55 by hyanagim          #+#    #+#             */
/*   Updated: 2023/01/14 06:51:03 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_args(t_vars *vars, int argc, char **argv)
{
	vars->args.num_of_philos = ft_atoi(argv[1]);
	vars->args.time_to_die = ft_atoi(argv[2]);
	vars->args.time_to_eat = ft_atoi(argv[3]);
	vars->args.time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		vars->args.times_must_eat = ft_atoi(argv[5]);
	else
		vars->args.times_must_eat = INT_MAX;
}

static void	init_forks(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->args.num_of_philos)
	{
		pthread_mutex_init(&vars->mtx_forks[i], NULL);
		i++;
	}
}

static void	init_philos(t_vars *vars)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < vars->args.num_of_philos)
	{
		philo = &vars->philos[i];
		philo->id = i + 1;
		philo->times_to_eat = 0;
		philo->last_eat_time = 0;
		if (philo->id == vars->args.num_of_philos)
			philo->status = THINKING_E;
		else if (philo->id % 2 == 0)
			philo->status = THINKING_E;
		else
			philo->status = EATING_E;
		philo->left = &vars->mtx_forks[i];
		if (i == 0)
			philo->right = &vars->mtx_forks[vars->args.num_of_philos - 1];
		else
			philo->right = &vars->mtx_forks[i - 1];
		philo->vars = vars;
		i++;
	}
}

void	init_vars(t_vars *vars, int argc, char **argv)
{
	struct timeval	now_time;

	init_args(vars, argc, argv);
	init_forks(vars);
	init_philos(vars);
	pthread_mutex_init(&vars->mtx_write, NULL);
	pthread_mutex_init(&vars->mtx_stop, NULL);
	pthread_mutex_init(&vars->mtx_time, NULL);
	gettimeofday(&now_time, NULL);
	vars->start_time = 1000 * now_time.tv_sec + now_time.tv_usec / 1000;
	vars->stop = false;
}
