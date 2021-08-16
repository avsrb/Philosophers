# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/time.h>


int	main(void)
{
	int i = 0;

	while (5 > i)
	{
		i += 2;
		if (i >= 5 && !(i % 2))
			i = 1;
		printf("%d\n", i);
	}


}