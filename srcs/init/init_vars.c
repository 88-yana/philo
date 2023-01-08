/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vars.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 18:50:55 by hyanagim          #+#    #+#             */
/*   Updated: 2023/01/09 03:52:43 by hyanagim         ###   ########.fr       */
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
		vars->args.times_to_eat_pasta = ft_atoi(argv[5]);
	else
		vars->args.times_to_eat_pasta = INT_MAX;
}

static void	init_forks(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->args.num_of_philos)
	{
		vars->forks[i].exist = true;
		pthread_mutex_init(&vars->forks[i].mtx, NULL);
		i++;
	}
}

static void	init_philos(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->args.num_of_philos)
	{
		vars->philos[i].id = i + 1;
		vars->philos[i].times_to_eat_pasta = vars->args.times_to_eat_pasta;
		vars->philos[i].last_eat_time = 0;
		if (vars->philos[i].id % 2 == 1)
			vars->philos[i].status = EATING_E;
		else
			vars->philos[i].status = THINKING_E;
		vars->philos[i].left = &vars->forks[i];
		if (i == 0)
			vars->philos[i].right = &vars->forks[vars->args.num_of_philos - 1];
		else
			vars->philos[i].right = &vars->forks[i - 1];
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
	gettimeofday(&now_time, NULL);
	vars->start_time = 1000 * now_time.tv_sec + now_time.tv_usec / 1000;
	vars->stop = false;
}
