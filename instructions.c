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

void  ft_print(t_philo *philo, int	status)
{
	char	*str;

	if (status == 0)
		str = "has taken a fork";
	else if (status == 1)
		str = "is eating";
	else if (status == 2)
		str = "is sleeping";
	else if (status == 3)
		str = "is thinking";
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%ld %d %s\n", get_time() - philo->data->start, philo->id, str);
	pthread_mutex_unlock(&philo->data->print_mutex);
}
void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	ft_print(philo, 0);
	pthread_mutex_lock(philo->right_fork);
	ft_print(philo, 0);
	ft_print(philo, 1);
	philo->last_meal = get_time();
	ft_usleep(philo->data->ttoeat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_lock(&philo->data->eat_mutex);
	philo->emeals++;
	pthread_mutex_unlock(&philo->data->eat_mutex);
}

void	ft_sleep(t_philo *philo)
{
	ft_print(philo, 2);
	ft_usleep(philo->data->ttosleep);
}

void	ft_think(t_philo *philo)
{
	ft_print(philo, 3);
}

void ft_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->death_mutex);
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%ld %d died\n", get_time() - philo->data->start, philo->id);
	philo->alive = false;
	pthread_mutex_lock(&philo->data->eat_mutex);
	pthread_mutex_lock(&philo->data->sleep_mutex);
}