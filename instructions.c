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

int  ft_print(t_philo *philo, int	status)
{
	char	*str;

	str = NULL;
	if (status == 0)
		str = "has taken a fork";
	else if (status == 1)
		str = "is eating";
	else if (status == 2)
		str = "is sleeping";
	else if (status == 3)
		str = "is thinking";
	pthread_mutex_lock(&philo->data->print_mutex);
	if (philo->data->end)
		return (pthread_mutex_unlock(&philo->data->print_mutex), 1);
	printf("%ld %d %s\n", get_time() - philo->data->start, philo->id, str);
	pthread_mutex_unlock(&philo->data->print_mutex);
	return (0);
}

int	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	if (ft_print(philo, 0))
		return (pthread_mutex_unlock(philo->left_fork), 1); //unlock before
	pthread_mutex_lock(philo->right_fork);
	if (ft_print(philo, 0))
		return (pthread_mutex_unlock(philo->left_fork), pthread_mutex_unlock(philo->right_fork), 1); // unllock before return 
	pthread_mutex_lock(&philo->lastm_mutex);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->lastm_mutex);
	if (ft_print(philo, 1))
		return (1);
	ft_usleep(philo->data->ttoeat, philo->data);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_lock(&philo->nmeals);
	philo->emeals++;
	pthread_mutex_unlock(&philo->nmeals);
	return (0);
}

int	ft_sleep(t_philo *philo)
{
	if (ft_print(philo, 2))
		return (1);
	ft_usleep(philo->data->ttosleep, philo->data);
	return (0);
}

int	ft_think(t_philo *philo)
{
	if (ft_print(philo, 3))
		return (1);
	return (0);
}
