/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyanagim <hyanagim@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/01 18:31:19 by hyanagim          #+#    #+#             */
/*   Updated: 2023/01/01 18:38:08 by hyanagim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (true);
	return (false);
}

int	ft_atoi(const char *str)
{
	long long	ans;
	int			sign;

	ans = 0;
	sign = -1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
		sign = *str++ - 44;
	while (ft_isdigit(*str))
		ans = ans * 10 - (long long)(*str++ - '0');
	return ((int) ans * sign);
}
