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

int	philosopher_init(t_data *data, char **av, t_philo **philo)
{
	data->nb_philo = ft_atoi(av[1]);
	data->ttodie = ft_atoi(av[2]);
	data->ttoeat = ft_atoi(av[3]);
	data->ttosleep = ft_atoi(av[4]);
	data->meals = -1;
	if (av[5])
		data->meals = ft_atoi(av[5]);
	if (create_mutexs(data) != 0)
		return (1);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return (mutex_destroy(data), 1);
	*philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (!*philo)
		return (mutex_destroy(data), free(data->forks), 1);
	return (0);
}

int	creation_philosopher(t_data *data, t_philo *philo)
{
	int	i;

	i = -1;
	data->start = get_time();
	while (++i < data->nb_philo)
	{
		philo[i].id = i + 1;
		philo[i].emeals = 0;
		philo[i].last_meal = data->start;
		philo[i].data = data;
		philo[i].left_fork = &data->forks[i];
		philo[i].right_fork = &data->forks[(i + 1) % data->nb_philo];
		if (pthread_mutex_init(&philo[i].lastm_mutex, NULL) != 0
			|| pthread_mutex_init(&data->forks[i], NULL) != 0
			|| pthread_mutex_init(&philo[i].nmeals, NULL) != 0)
			return (write(2, "Error: mutex init failed\n", 26), -1);
	}
	return (0);
}

int	philosophers(t_data *data, char **tab)
{
	t_philo	*philo;
	int		stat;

	if (philosopher_init(data, tab, &philo) !=0)
		return (printf("Error\n"), -1);
	if (creation_philosopher(data, philo) < 0)
		return (ft_free(data, philo), -1);
	stat = simulation(data, philo);
	if (stat < 0)
		return (ft_free(data, philo), -1);
	ft_end_sim(data, philo);
	return (0);
}

int main(int ac, char **av)
{
	t_data	data;
	int		i; 

	if (ac < 5 || ac > 6)
		return (print_instruction(), 1);
	i = parser(ac, av);
	if (i == 1)
		return (write(2, "Error\n", 7), -1);
	philosophers(&data, av);
	return 0;
}