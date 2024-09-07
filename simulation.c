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

void	ft_end_simulation(t_data *data, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
	{
		pthread_mutex_unlock(&data->forks[i]);
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_unlock(&philo[i].lastm_mutex);
		pthread_mutex_destroy(&philo[i].lastm_mutex);
		pthread_mutex_unlock(&philo[i].nmeals);
		pthread_mutex_destroy(&philo[i].nmeals);
	}
	pthread_mutex_unlock(&data->death_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	pthread_mutex_unlock(&data->eat_mutex);
	pthread_mutex_destroy(&data->eat_mutex);
	pthread_mutex_unlock(&data->sleep_mutex);
	pthread_mutex_destroy(&data->sleep_mutex);
	// pthread_mutex_unlock(&data->print_mutex);
	pthread_mutex_destroy(&data->print_mutex);
	// ft_free(data, philo);
	printf("\t\t\tSimulation ended\n");
	exit(0);
}

int	loop_philo(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->data->nb_philo)
	{
		pthread_mutex_lock(&philo[i].data->eat_mutex);
		if (philo[i].emeals < philo->data->meals)
			return (pthread_mutex_unlock(&philo[i].data->eat_mutex), 0);
		pthread_mutex_unlock(&philo[i].data->eat_mutex);
	}
	return (pthread_mutex_lock(&philo->data->print_mutex), 1);
}

int	monitoring(t_philo *philo, t_data *data)
{
	int	i;

	while (1)
	{
		i = -1;
		// if (data->meals == 0)
		// 	return (data->alive = false, NULL);
		while (++i < data->nb_philo)
		{
			if (data->meals > 0 && loop_philo(philo) == 1)
				return (1);
			pthread_mutex_lock(&philo[i].lastm_mutex);
			if (get_time() - philo[i].last_meal >= (size_t)(data->ttodie))
			{
				pthread_mutex_lock(&philo[i].data->death_mutex);
				pthread_mutex_lock(&philo[i].data->print_mutex);
				printf("%zu %d %s\n", get_time() - philo[i].data->start,
					philo[i].id, "died");
				// pthread_mutex_unlock(&philo[i].data->print_mutex);
				philo[i].alive = false;
				pthread_mutex_unlock(&philo[i].data->death_mutex);
				return (1);
			}
			pthread_mutex_unlock(&philo[i].lastm_mutex);
		}
	}
	return (0);
}

void	*routine(void *argument)
{
	t_philo	*philo;
	
	philo = (t_philo *)argument;
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->ttoeat);
	while (philo->emeals < philo->data->meals || philo->data->meals == -1)
	{
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
		// if (philo->data->meals > 0)
		// 	philo->data->meals--;
	}
	return (NULL);
}

int	simulation(t_data *data, t_philo *philo)
{
	int	i;
	// int	stat;

	i = -1;
	while (++i < philo->data->nb_philo)
	{
		if (pthread_create(&philo[i].philo_th, NULL, &routine, &philo[i]) != 0)
			return (write(2, "Error: thread creation failed\n", 30), -1);
		pthread_detach(philo[i].philo_th);
	}
	// stat = monitoring(philo, data);
	monitoring(philo, data);
	// if (stat == 1)
	// 	ft_end_simulation(data, philo);
	return (0);
}
