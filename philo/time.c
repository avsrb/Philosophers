#include "philo.h"

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	ft_sleep(long long time)
{
	long long	start;
	long long	now;

	start = timestamp();
	now = start;

	while (time > now - start)
	{
		now = timestamp();
		usleep(300);
	}
	return ;
}
