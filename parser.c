/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmaghdao <zmaghdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 22:14:16 by zmaghdao          #+#    #+#             */
/*   Updated: 2024/08/05 22:14:16 by zmaghdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosopher.h"

void	print_instruction(void)
{
	printf("\t\tWRONG INPUT!\n\n");
	printf("./philo [nb_philos] [time_to_die] ");
	printf("[time_to_eat time_to_sleep] ");
	printf("[number_of_meals_that_each_philosopher_must_eat] ");
	printf("(optional argument)\n");
	printf("Example:\n");
	printf("./philo 4 800 200 200 5\n\n");
	printf("nb_philos value: 1-200\n");
	printf("time_to_die value: 60+\n");
	printf("time_to_eat value: 60+\n");
	printf("time_to_sleep value: 60+\n");
	printf("number_of_times_each_philosopher_must_eat ");
	printf("value: 0+\n");
}

int	check_strings(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (!str[i])
		return (1);
	while (str[i])
	{
		if ((str[i] == '+') && (str[i + 1] == '+' || !str[i + 1]))
			return (1);
		if ((str[i] >= '0' && str[i] <= '9')
			&& !((str[i + 1] >= '0' && str[i + 1] <= '9') || !str[i + 1]))
			return (1);
		if ((str[i] < '0' || str[i] > '9') && str[i] != '+')
			return (1);
		i++;
	}
	return (0);
}

int parser(int ac, char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (check_strings(av[i]) != 0)
			return (1);
		if ((ac == 5) && ((ft_atoi(av[i]) < 60 && i > 1)
		|| ((ft_atoi(av[i]) <= 0 || ft_atoi(av[i]) > 200) && i == 1)))
			return (1);
		else if ((ac == 6) && ((ft_atoi(av[i]) < 60 && i > 1 && i < ac - 1)
		|| ((ft_atoi(av[i]) <= 0 || ft_atoi(av[i]) > 200) && i == 1)
		|| (ft_atoi(av[ac - 1]) < 0)))
			return (1);
		i++;
	}
	return (0);
}
