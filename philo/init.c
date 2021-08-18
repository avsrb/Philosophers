#include "philo.h"

int	mem_allocation(t_data *data)
{
	data->ph = malloc(sizeof(*data->ph) * data->table->nbr_ph);
	if (data->ph == 0)
		return (-1);
	data->table->forks = malloc(sizeof(*data->table->forks) \
								* data->table->nbr_ph);
	if (data->ph == 0)
		return (-1);
	return (0);
}

int	mem_free(t_data *data)
{	
	int	i;

	i = 0;
	while (i < data->table->nbr_ph)
	{
		if (pthread_detach(data->ph[i].thread_id))
			return (-1);
		i++;
	}
	free(data->ph);
	free(data->table->forks);
	return (0);
}

int	init_mutexes(t_table *table)
{
	int	i;

	i = 0;
	while (table->nbr_ph > i)
	{
		if (pthread_mutex_init(table->forks + i, NULL))
			return (-1);
		i++;
	}
	if (pthread_mutex_init(&table->message, NULL))
		return (-1);
	return (0);
}

void	init_philos(t_data *d)
{
	int	i;

	i = 0;
	while (i < d->table->nbr_ph)
	{
		d->ph[i].ph_id = i + 1;
		d->ph[i].left_fork = &d->table->forks[i];
		d->ph[i].right_fork = &d->table->forks[(i + 1) % d->table->nbr_ph];
		d->ph[i].ate = 0;
		i++;
	}
	return ;
}

int	init(t_data *data)
{
	int	i;

	i = 0;
	if (mem_allocation(data))
		return (write_error("mem_allocation"));
	if (init_mutexes(data->table))
		return (write_error("Init mutex"));
	init_philos(data);
	return (0);
}
