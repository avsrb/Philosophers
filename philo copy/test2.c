#include "philo_one.h"

typedef struct 
{
	int	i;
	pthread_mutex_t* left;
	pthread_mutex_t* right;
} Struct;

pthread_mutex_t	mutex1;
pthread_mutex_t	mutex2;

void	*print(void *sructure)
{
	Struct s = *(Struct *)sructure;
	usleep(1000);
	for (int i = 0; i < 5; i++)
	{
		pthread_mutex_lock(s.left);
		pthread_mutex_lock(s.right);

		printf("Thread = %d\n", s.i);
		pthread_mutex_unlock(s.left);
		pthread_mutex_unlock(s.right);
	}
	printf("end\n");
	return(0);
}

void	threads()
{
	pthread_t t1, t2;

	pthread_mutex_init(&mutex1, NULL);
	pthread_mutex_init(&mutex2, NULL);
	Struct s1, s2;
	s1.i = 1;
	s1.left = &mutex1;
	s1.right = &mutex2;

	s2.i = 2;
	s2.left = &mutex2;
	s2.right = &mutex1;

	pthread_create(&t1, NULL, print, (void *)&s1);
	pthread_create(&t2, NULL, print, (void *)&s2);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	write(1, "Exit\n", 5);
}


int	main(void)
{
	threads();
}