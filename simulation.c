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
		pthread_mutex_unlock(&data->forks[i]);
	ft_free(data, philo);
}

void	*monitoring(t_philo *philo, t_data *data)
{
		int	i;

	while (1)
	{
		i = -1;
		while (++i < data->nb_philo)
		{
			if (pthread_mutex_lock(&philo[i].data->death_mutex)
				|| pthread_mutex_lock(&philo[i].data->print_mutex))
				return (NULL);
			if (get_time() - philo[i].last_meal >= (size_t)(data->ttodie))
			{
				printf("%zu %d %s\n", get_time() - philo[i].data->start,
					philo[i].id, "died");
				return (data->alive = false, NULL);
			}
			pthread_mutex_unlock(&philo[i].data->print_mutex);
			pthread_mutex_unlock(&philo[i].data->death_mutex);
			pthread_mutex_lock(&philo[i].data->eat_mutex);
			if (data->emeals >= data->nb_philo)
				return (NULL);
			pthread_mutex_unlock(&philo[i].data->eat_mutex);
		}
	}
	return (NULL);
}

void	*routine(void *argument)
{
	t_philo	*philo;
	int		i;
	
	philo = (t_philo *)argument;
	i = -1;
	while (++i < philo->data->nb_philo)
		if (philo->id % 2 == 0)
			usleep(2000);
	while (philo->data->meals != 0 || philo->emeals < philo->data->meals)
	{
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
		if (philo->data->meals > 0)
			philo->data->meals--;
	}
	puts("i was here btw !");
	return (NULL);
}

int	simulation(t_data *data, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->data->nb_philo)
	{
		if (pthread_create(&philo[i].philo_th, NULL, &routine, &philo[i]) != 0)
			return (write(2, "Error: thread creation failed\n", 30), -1);
	}
    i = -1;
    while (++i < philo->data->nb_philo)
        pthread_detach(philo[i].philo_th);
	monitoring(philo, data);
	return (0);
}

    // i = -1;
	// while (i++ < philo->data->nb_philo)
	// {
    //     if (!philo->alive || !data->alive)
    //     {
    //         pthread_mutex_lock(&data->print_mutex);
    //         printf("==== end of simulation [a philo died] ===\n");
    //         pthread_mutex_unlock(&data->print_mutex);
    //         ft_end_simulation(data, philo);
    //         return (0);
    //     }
    // }