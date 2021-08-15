# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <sys/time.h>

#define PHT 5
pthread_mutex_t entry_point = PTHREAD_MUTEX_INITIALIZER;


typedef struct s_ph
{
	char	*name;
	unsigned	left_fork;
	unsigned	right_fork;
}			t_ph;

typedef struct s_table
{
	pthread_mutex_t	forks[PHT];
}		t_table;

typedef struct s_data
{
	t_ph		*philo;
	t_table	*table;
}		t_data;

void	init_philo(t_ph *ph, char *name, unsigned left_fork, unsigned right_fork)
{
	ph->name = name;
	ph->left_fork = left_fork;
	ph->right_fork = right_fork;
}
void	init_table(t_table *table)
{
	size_t	i;
	for(i = 0; i < PHT; i++)
		pthread_mutex_init(&table->forks[i], NULL);
}

void	*eat(void *v_data)
{
	t_data	*data = (t_data *)v_data;
	t_ph *philo = data->philo;
	t_table *table = data->table;

	printf("%s started dinner\n", philo->name);

	pthread_mutex_lock(&entry_point);
	pthread_mutex_lock(&table->forks[philo->left_fork]);
	//sleep(1);
	pthread_mutex_lock(&table->forks[philo->right_fork]);
	pthread_mutex_unlock(&entry_point);

	printf("%s is eating\n", philo->name);

	pthread_mutex_unlock(&table->forks[philo->left_fork]);
	pthread_mutex_unlock(&table->forks[philo->right_fork]);

	printf("%s is finished dinner\n", philo->name);
	return (0);
}

int	main(void)
{
	pthread_t	threads[PHT];

	t_ph		phs[PHT];
	t_data		data[PHT];
	t_table		table;
	size_t		i;
	
	
	init_table(&table);
	init_philo(&phs[0], "1", 0, 1);
	init_philo(&phs[1], "2", 1, 2);
	init_philo(&phs[2], "3", 2, 3);
	init_philo(&phs[3], "4", 3, 4);
	init_philo(&phs[4], "5", 4, 0);

	for (i = 0; i < PHT; i++)
	{
		data[i].philo = &phs[i];
		data[i].table = &table;
	}
	for (i = 0; i <PHT; i++)
	{
		pthread_create(&threads[i], NULL, eat, &data[i]);
	}
	for (i = 0; i <PHT; i++)
	{
		pthread_join(threads[i], NULL);
	}
	wait(0);
}