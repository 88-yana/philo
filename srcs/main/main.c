/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 15:23:24 by hyanagim          #+#    #+#             */
/*   Updated: 2023/01/09 04:12:19 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "string.h"

int	main(int argc, char **argv)
{
	t_vars	vars;

	memset(&vars, 0, sizeof(t_vars));
	if (check_args(argc, argv) == false)
		return (1);
	init_vars(&vars, argc, argv);
	printf("LINE == %d, FILE == %s\n", __LINE__, __FILE__);
	create_philos_threads(&vars);
	// create_monitor_thread(&vars);
	printf("LINE == %d, FILE == %s\n", __LINE__, __FILE__);
	join_threads(&vars);
	destroy_mutexes(&vars);
	printf("num is %d\n", vars.args.num_of_philos);
	printf("LINE == %d, FILE == %s\n", __LINE__, __FILE__);
	printf("die is %d\n", vars.args.time_to_die);
	printf("LINE == %d, FILE == %s\n", __LINE__, __FILE__);
	printf("eat is %d\n", vars.args.time_to_eat);
	printf("sleep is %d\n", vars.args.time_to_sleep);
	printf("times is %d\n", vars.args.times_to_eat_pasta);
	printf("%s\n", "ok");
	printf("LINE == %d, FILE == %s\n", __LINE__, __FILE__);
	return (0);
}
