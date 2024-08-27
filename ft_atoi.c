/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmaghdao <zmaghdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 22:14:32 by zmaghdao          #+#    #+#             */
/*   Updated: 2024/08/05 22:14:32 by zmaghdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosopher.h"

static int	ft_check(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+')
		i++;
	return (i);
}

long	ft_atoi(const char *str)
{
	int		i;
	long	res;

	res = 0;
	i = ft_check(str);
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		res = (res * 10) + (str[i] - 48);
		if (res > 2147483647 || res < 0)
		{
			if (res < 0)
				return(write(2, "negative !!\n", 13), 0);
			else
			return(write(2, "> overflow !!\n", 14), -1);
		}
		i++;
	}
	return (res);
}
