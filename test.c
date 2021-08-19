# include <pthread.h>
# include <semaphore.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/time.h>
# include <limits.h>

int main(void)
{
	int	*num;
	int	i;

	i = 0;
	num = malloc(sizeof(*num) * 10);

	while (i < 5)
	{
		num[i - 1] = fork();
		if (num[i - 1])
			i++;
		else
		{
			printf("%d PID\n", getpid());
			printf("%d hello\n", i);
			exit(1);
		}
		// sleep(10);
	}
	return (0);
}