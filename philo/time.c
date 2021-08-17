#include "philo.h"

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return((t.tv_sec * 1000) + (t.tv_usec /1000));
}

void	ft_sleep(long long time)
{
	while (time - timestamp() > 0)
	{
		usleep(100);
	}
	return ;
}
