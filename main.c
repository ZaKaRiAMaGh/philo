#include "philosopher.h"

// void	*function()
// {
// 	printf("here is the vest\n");
// }

int main(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (write(2, "please run the program like :\n"
		"./philosopher nphilos tdie teat tsleep nmeals(optional)!\n", 88), 1);
	int	i;
	int	*tab;
	// pthread_t t1;
	// else 
	// {
	//	 pthread_create(&t1, NULL, &function, NULL);
	//	 pthread_join(t1,NULL);
	// }
	i = parser(ac, av, &tab);
	if (i == 1)
		return (printf("Error\n"), -1);
	else
		printf("sal7a\n");
	for (int h = 0; h < ac - 1; h++)
		printf("%d\n", tab[h]);
	return 0;
}