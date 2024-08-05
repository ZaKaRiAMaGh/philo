

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>

int		parser(int ac, char **av, int **tab);
long	ft_atoi(const char *str);
#endif