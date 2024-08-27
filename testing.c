int	mails = 0;

pthread_mutex_t mutex;

void	*function()
{
	// printf("here is the vest\n");//t1 : 620 t2 :601 r inc w
	for (size_t i = 0; i < 60000; i++)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		printf("mails : %d\n", mails);
		pthread_mutex_unlock(&mutex);
		sleep(0.8);
	}
}

int main(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (write(2, "please run the program like :\n"
		"./philosopher nphilos tdie teat tsleep nmeals(optional)!\n", 88), 1);
	(void)ac;
	(void)av;
	int	i;
	int	*tab;
	pthread_t t1, t2;
	pthread_create(&t1, NULL, &function, NULL);
	pthread_create(&t2, NULL, &function, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_mutex_init(&mutex, NULL);
	i = parser(ac, av, &tab);
	if (i == 1)
		return (printf("Error\n"), -1);
	else
		printf("sal7a\n");
	// for (int h = 0; h < ac - 1; h++)
	// 	printf("%d\n", tab[h]);
	printf("mails : %d\n", mails);
	return 0;
}