/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 15:23:24 by hyanagim          #+#    #+#             */
/*   Updated: 2023/01/09 16:34:50 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "string.h"

void	create_threads(t_vars *vars)
{
	int		i;

	i = 0;
	while (i < vars->args.num_of_philos)
	{
		pthread_create(&vars->philos[i].thd, NULL, philo_act, &vars->philos[i]);
		i++;
	}
	pthread_create(&vars->monitor.thd, NULL, monitor_act, vars);
}

void	join_threads(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->args.num_of_philos)
	{
		pthread_join(vars->philos[i].thd, NULL);
		i++;
	}
	pthread_join(vars->monitor.thd, NULL);
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
	pthread_mutex_destroy(&vars->mtx_write);
	pthread_mutex_destroy(&vars->mtx_stop);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	memset(&vars, 0, sizeof(t_vars));
	if (check_args(argc, argv) == false)
		return (1);
	init_vars(&vars, argc, argv);
	create_threads(&vars);
	join_threads(&vars);
	destroy_mutexes(&vars);
	return (0);
}

	// printf("num is %d\n", vars.args.num_of_philos);
	// printf("die is %d\n", vars.args.time_to_die);
	// printf("eat is %d\n", vars.args.time_to_eat);
	// printf("sleep is %d\n", vars.args.time_to_sleep);
	// printf("times is %d\n", vars.args.times_to_eat_pasta);
	// printf("%s\n", "ok");