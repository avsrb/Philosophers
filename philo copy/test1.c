#include "philo_one.h"

pthread_mutex_t mutex; // посути это вилки

void	print_arr(int arr[])
{
	int i = 0; 
	while(arr[i])
	{
		printf("%d ", arr[i]);
		i++;
	}
	printf("\n");
}

void	*print(void *arr)
{
	pthread_mutex_lock(&mutex);

	for (int i = 0; i < 20; i++)
		((int *)arr)[i] += i;
	print_arr((int *)arr);

	for (int i = 0; i < 20; i++)
		((int *)arr)[i] -= i;
	print_arr((int *)arr);
	
	pthread_mutex_unlock(&mutex);

	write(1, "end\n", 4);
	return (NULL);
}

void	threads()
{
	int	arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};

	pthread_t	t1, t2;
	pthread_mutex_init(&mutex, NULL);

	pthread_create(&t1, NULL, print, (void *)arr);
	pthread_create(&t2, NULL, print, (void *)arr);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	write(1, "Exit\n", 5);
}



int	main(void)
{
	threads();
	
}