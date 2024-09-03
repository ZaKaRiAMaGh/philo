/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmaghdao <zmaghdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 22:14:06 by zmaghdao          #+#    #+#             */
/*   Updated: 2024/08/05 22:14:06 by zmaghdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>

typedef struct s_data t_data;

typedef struct s_philo
{
	int					id;
	int					emeals;
	size_t				last_meal;
	bool 				alive;
	pthread_t			philo_th;
	pthread_mutex_t		*left_fork;
	pthread_mutex_t		*right_fork;
	t_data				*data;
}	t_philo;

typedef struct s_data
{
	int					nb_philo;
	int					ttodie;
	int					ttoeat;
	int					ttosleep;
	int					meals;
	int					emeals;
	bool				alive;
	pthread_mutex_t		*forks;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		death_mutex;
	pthread_mutex_t		eat_mutex;
	pthread_mutex_t		sleep_mutex;
	size_t				start;
}	t_data;


int		parser(int ac, char **av);
long	ft_atoi(const char *str);
void	print_instruction(void);
size_t	get_time(void);
void	ft_usleep(size_t time);
void	ft_free(t_data *data, t_philo *philo);
void	mutex_destroy(t_data *data);
int		create_mutexs(t_data *data);

int		simulation(t_data *data, t_philo *philo);
void	*routine(void *argument);

void	ft_eat(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	ft_think(t_philo *philo);
void	ft_death(t_philo *philo);

#endif