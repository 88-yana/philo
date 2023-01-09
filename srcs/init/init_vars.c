/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 18:50:55 by hyanagim          #+#    #+#             */
/*   Updated: 2023/01/09 22:33:21 by hyanagim         ###   ########.fr       */
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
		vars->args.max_eat = ft_atoi(argv[5]);
	else
		vars->args.max_eat = INT_MAX;
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
	int	i;
	int	num_of_philos;

	num_of_philos = vars->args.num_of_philos;
	i = 0;
	while (i < num_of_philos)
	{
		vars->philos[i].id = i + 1;
		vars->philos[i].max_eat = vars->args.max_eat;
		vars->philos[i].last_eat_time = 0;
		if (vars->args.max_eat == 0 || vars->philos[i].id == num_of_philos)
			vars->philos[i].status = THINKING_E;
		else if (vars->philos[i].id % 2 == 1)
			vars->philos[i].status = EATING_E;
		else
			vars->philos[i].status = THINKING_E;
		vars->philos[i].left = &vars->mtx_forks[i];
		if (i == 0)
			vars->philos[i].right = &vars->mtx_forks[num_of_philos - 1];
		else
			vars->philos[i].right = &vars->mtx_forks[i - 1];
		vars->philos[i].vars = vars;
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
