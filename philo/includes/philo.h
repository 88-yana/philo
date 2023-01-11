/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 15:05:33 by hyanagim          #+#    #+#             */
/*   Updated: 2023/01/11 15:27:40 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <limits.h>
# include <sys/time.h>
# include <unistd.h>
# include <pthread.h>
# include "libft.h"

# define MAX_PHILO 200
# define STOP_WRITE -1
# define TAKEN_A_FORK_STR "has taken a fork"
# define EATING_STR "is eating"
# define SLEEPING_STR "is sleeping"
# define THINKING_STR "is thinking"
# define DIED_STR "died"

typedef struct s_vars	t_vars;

typedef enum e_status
{
	EATING_E,
	SLEEPING_E,
	THINKING_E
}	t_status;

typedef struct s_philo
{
	pthread_t		thd;
	int				id;
	int				max_eat;
	int				last_eat_time;
	t_status		status;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	t_vars			*vars;
}	t_philo;

typedef struct s_args
{
	int	num_of_philos;
	int	time_to_eat;
	int	time_to_sleep;
	int	time_to_die;
	int	max_eat;
}	t_args;

struct s_vars
{
	t_args			args;
	t_philo			philos[MAX_PHILO];
	int				start_time;
	bool			stop;
	pthread_t		monitor;
	pthread_mutex_t	mtx_forks[MAX_PHILO];
	pthread_mutex_t	mtx_time;
	pthread_mutex_t	mtx_write;
	pthread_mutex_t	mtx_stop;
};

bool	check_args(int argc, char **argv);
void	init_vars(t_vars *vars, int argc, char **argv);

bool	log_manager(int timestamp, t_philo *philo, t_vars *vars, t_status type);
void	*monitor_act(void *arg);
void	*philo_act(void *arg);
int		get_timestamp(int start_time);
void	stop_while_eating(int timestamp, t_philo *philo, int time_to_do);

bool	is_dead(int timestamp, int last_eat_time, int time_to_die);
bool	can_eat(t_philo *philo);
void	lock_mutex(t_philo *philo, t_vars *vars, t_status type);
void	unlock_mutex(t_philo *philo, t_vars *vars, t_status type);

#endif