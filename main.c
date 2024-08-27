/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmaghdao <zmaghdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 22:14:26 by zmaghdao          #+#    #+#             */
/*   Updated: 2024/08/05 22:14:26 by zmaghdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosopher.h"

int	philosopher_init(t_philo *philo, char **av)
{
	philo->nb_philo = ft_atoi(av[1]);
	philo->ttodie = ft_atoi(av[2]);
	philo->ttoeat = ft_atoi(av[3]);
	philo->ttosleep = ft_atoi(av[4]);
	if (av[5])
		philo->meals = ft_atoi(av[5]);
	else
		philo->meals = 0;
	if (gettimeofday(&philo->time, NULL) != 0)
		return (write(2, "gettimeofday error\n", 19), 1);
	return (0);
}

void	philosophers(t_philo *philo, char **tab)
{
	philosopher_init(philo, tab);
}

int main(int ac, char **av)
{
	t_philo philo;
	int		i;

	if (ac < 5 || ac > 6)
		return (print_instruction(), 1);
	i = parser(ac, av);
	if (i == 1)
		return (printf("Error\n"), -1);
	philosophers(&philo, av);
	printf("mails : %d\n", mails);
	return 0;
}