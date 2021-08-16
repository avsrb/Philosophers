#include "philo_one.h"

int	mails = 0;
pthread_mutex_t	mutex;

void	*routine()
{
	for(int i = 0; i < 1000000; i++) {
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
	}
	return (NULL);
}

int	main(int agrc, char **agrv)
{
	pthread_t th[8];
	int i;
	
	pthread_mutex_init(&mutex, NULL);
	for(i = 0; i < 8; i++)
	{
		if (pthread_create(th + i, NULL, &routine, NULL) != 0)
		{
			perror("Failed ti created thread");
			return (1);
		}
		printf("Thread %d has started\n", i);
	}
	for(i = 0; i < 8; i++)
	{
		if (pthread_join(th[i], NULL) != 0)
		return (2);
		printf("Thread %d has finished execution\n", i);
	}
	printf("Number of mails: %d\n", mails);
	return (0);
}