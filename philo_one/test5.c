# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/time.h>

unsigned long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	// printf("%ld\n", t.tv_sec);
	// printf("%d\n", t.tv_usec);
	
	return((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

int	main(void)
{
	unsigned long long t;
	unsigned long long t1;
	unsigned long long t2;

	t = timestamp();
	t1 = timestamp();
	t2 = timestamp();
	printf("%llu\n", timestamp() - timestamp());


}