#include "philo.h"

uint64_t	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	ft_sleep(uint64_t time)
{
	uint64_t	start;

	start = timestamp();
	while (time > timestamp() - start)
		usleep(100);
	return ;
}
