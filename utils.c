/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmaghdao <zmaghdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 08:12:59 by zmaghdao          #+#    #+#             */
/*   Updated: 2024/08/27 08:12:59 by zmaghdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosopher.h"

void	ft_usleep(size_t time, t_data *data)
{
	size_t	start;

	start = get_time();
	while (get_time() - time < start)//check the end bool
	{
		pthread_mutex_lock(&data->print_mutex);
		if (data->end)
		{
			(pthread_mutex_unlock(&data->print_mutex));
			return ;
		}
		pthread_mutex_unlock(&data->print_mutex);
		usleep(200);
	}
}

size_t	get_time(void)
{
	struct timeval	time;
	
	if (gettimeofday(&time, NULL) != 0)
		return (write(2, "gettimeofday error !\n", 22), -1);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_free(t_data *data, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < data->nb_philo)
		pthread_mutex_destroy(&data->forks[i]);
	free(data->forks);
	free(philo);
	mutex_destroy(data);
}

void	mutex_destroy(t_data *data)
{
	pthread_mutex_destroy(&data->print_mutex);
}

int	create_mutexs(t_data *data)
{
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (write(2, "Error: mutex init failed\n", 26), 1);
	return (0);
}
