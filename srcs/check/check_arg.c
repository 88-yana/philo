/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 15:40:30 by hyanagim          #+#    #+#             */
/*   Updated: 2023/01/04 18:48:28 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	is_number(char *str)
{
	int	i;

	if (str == NULL)
		return (false);
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (i < ft_strlen(str))
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

static bool	is_int(char *str)
{
	int	ans;
	int	sign;

	if (str == NULL || *str == '-')
		return (false);
	ans = 0;
	sign = -1;
	if (*str == '+')
		sign = *str++ - 44;
	while (ft_isdigit(*str))
	{
		if (sign * ans > (INT_MAX - (int)(*str - '0')) / 10)
			return (false);
		ans = ans * 10 - (int)(*str++ - '0');
	}
	return (true);
}

static bool	is_valid_number(char **array, int i)
{
	while (array[i])
	{
		if (is_number(array[i]) == false)
			return (false);
		if (is_int(array[i]) == false)
			return (false);
		i++;
	}
	return (true);
}

bool	check_arg(int argc, char **argv)
{
	if (argc < 5 || 6 < argc)
	{
		printf("args: num_of_philos die eat sleep (times_of_eating)\n");
		return (false);
	}
	if (is_valid_number(argv, 1) == false)
	{
		printf("args are invalid\n");
		return (false);
	}
	if (ft_atoi(argv[1]) < 1 || 200 < ft_atoi(argv[1]))
	{
		printf("there are too many philos or less than 1\n");
		return (false);
	}
	if (argc == 6 && ft_atoi(argv[5]) == 0)
	{
		printf("%d 1 %s\n", ft_atoi(argv[2]) + 1, DIED_STR);
		return (false);
	}
	return (true);
}
