/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmaghdao <zmaghdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 22:14:16 by zmaghdao          #+#    #+#             */
/*   Updated: 2024/08/05 22:14:16 by zmaghdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosopher.h"

int	check_strings(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (!str[i])
		return (1);
	while (str[i])
	{
		if ((str[i] == '+') && (str[i + 1] == '+' || !str[i + 1]))
			return (1);
		if ((str[i] >= '0' && str[i] <= '9')
			&& !((str[i + 1] >= '0' && str[i + 1] <= '9') || !str[i + 1]))
			return (1);
		if ((str[i] < '0' || str[i] > '9') && str[i] != '+')
			return (1);
		i++;
	}
	return (0);
}

int parser(int ac, char **av, int **tab)
{
	int	i;
	int	j;

	*tab = malloc(sizeof(int) * (ac - 1));
	if (!*tab)
		return (write(2, "allocation !\n", 14), 1);
	i = 1;
	j = 0;
	while (av[i])
	{
		if (check_strings(av[i]) != 0)
			return (1);
		if ((ac == 5) && ((ft_atoi(av[i]) < 60 && i > 1)
		|| ((ft_atoi(av[i]) <= 0 || ft_atoi(av[i]) > 200) && i == 1)))
			return (1);
		else if ((ac == 6) && ((ft_atoi(av[i]) < 60 && i > 1 && i < ac - 1)
		|| ((ft_atoi(av[i]) <= 0 || ft_atoi(av[i]) > 200) && i == 1)
		|| (ft_atoi(av[ac - 1]) < 0)))
			return (1);
		i++;
	}
	i = 1;
	while (av[i])
		(*tab)[j++] = ft_atoi(av[i++]);
	return (0);
}
