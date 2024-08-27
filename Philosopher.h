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

typedef pthread_mutex_t	t_mutex;

typedef struct s_time
{
	long	sec;
	long	microsec;
}	t_time;

typedef struct s_philo
{
	int			nb_philo;
	int			ttodie;
	int			ttoeat;
	int			ttosleep;
	int			meals;
	t_mutex		mutex;
	t_mutex		*forks;
	pthread_t	*philo;
	t_time		time;
}	t_philo;


int		parser(int ac, char **av);
long	ft_atoi(const char *str);
void	print_instruction(void);

#endif