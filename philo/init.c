#include "philo.h"

int	mem_allocation(t_data *data)
{
	data->ph = malloc(sizeof(*data->ph) * data->table->nbr_ph);
	if (data->ph == 0)
		return (-1);
	data->table->forks = malloc(sizeof(*data->table->forks) * data->table->nbr_ph);
	if (data->ph == 0)
		return (-1);
	return (0);
}
int	init_mutexes(t_table *table)
{
	int	i;
	
	i = 0;
	while (table->nbr_ph > i)
	{
		// printf("%d\n", i);
		if (pthread_mutex_init(table->forks + i, NULL))
			return (-1);
		i++;
	}
	if (pthread_mutex_init(&table->message, NULL))
		return (-1);
	return (0);
}

void	init_philos(t_data *data)
{
	int	i;

	i = 0;

	while (i < data->table->nbr_ph)
	{
		data->ph[i].ph_id = i + 1;
		data->ph[i].left_fork = i;
		data->ph[i].right_fork = (i + 1) % data->table->nbr_ph;
		data->ph[i].ate = 0;
		i++;
	}
	return ;
}

int	init(t_data *data)
{
	int	i;

	i = 0;
	if (mem_allocation(data))
		return(write_error("mem_allocation"));
	if (init_mutexes(data->table))
		return(write_error("Init mutex"));
	init_philos(data);
	return (0);
}