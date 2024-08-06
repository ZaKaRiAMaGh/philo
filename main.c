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

int	mails = 0;

void	*function()
{
	// printf("here is the vest\n");//t1 : 620 t2 :601 r inc w
	for (size_t i = 0; i < 60000; i++)
		mails++;
}

int main(int ac, char **av)
{
	// if (ac < 5 || ac > 6)
	// 	return (write(2, "please run the program like :\n"
	// 	"./philosopher nphilos tdie teat tsleep nmeals(optional)!\n", 88), 1);
	(void)ac;
	(void)av;
	// int	i;
	// int	*tab;
	pthread_t t1, t2;
	pthread_create(&t1, NULL, &function, NULL);
	pthread_create(&t2, NULL, &function, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	// i = parser(ac, av, &tab);
	// if (i == 1)
	// 	return (printf("Error\n"), -1);
	// else
	// 	printf("sal7a\n");
	// for (int h = 0; h < ac - 1; h++)
	// 	printf("%d\n", tab[h]);
	printf("mails : %d\n", mails);
	return 0;
}