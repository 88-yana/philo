/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 15:05:33 by hyanagim          #+#    #+#             */
/*   Updated: 2023/01/06 19:38:31 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <limits.h>
# include <sys/time.h>
# include <pthread.h>
# include "libft.h"

# define MAX_PHILO 200
# define TAKEN_A_FORK "has taken a fork"
# define EATING_STR "is eating"
# define SLEEPING_STR "is sleeping"
# define THINKING_STR "is thinking"
# define DIED_STR "died"

typedef enum e_status
{
	EATING_E,
	SLEEPING_E,
	THINKING_E
}	t_status;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	int				id; //本当に必要か？
	bool			exist; //存在しなければ取れない//1のときしか考えない
}	t_fork;
typedef struct s_philo
{
	pthread_t		thread;
	pthread_mutex_t	mutex; //いらないかも
	int				id;
	int				times_to_eat_pasta;
	t_status		state;
	t_fork			*left;
	t_fork			*right;
	t_vars			*vars;
}	t_philo;

typedef struct s_monitor
{
	pthread_t		thread;
	pthread_mutex_t	alive;
}	t_monitor;
typedef struct s_args
{
	int	num_of_philos;
	int	time_to_eat;
	int	time_to_sleep;
	int	time_to_die;
	int	times_to_eat_pasta;
}	t_args;

typedef struct s_vars
{
	t_args		args;
	t_philo		philos[MAX_PHILO];
	t_monitor	monitor;
	t_fork		forks[MAX_PHILO];
	int			start_time;
	bool		go_on;
}	t_vars;

bool	check_args(int argc, char **argv);
void	init_vars(t_vars *vars, int argc, char **argv);

#endif