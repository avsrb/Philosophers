/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshmelly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 13:35:09 by mshmelly          #+#    #+#             */
/*   Updated: 2021/08/09 13:35:12 by mshmelly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return((t.tv_sec * 1000) + (t.tv_usec /1000));
}

void	ft_message(t_data *data, int ph_id, char *str)
{
	printf("msg\n");
	pthread_mutex_lock(&data->table->message);
	// if(!(data->dieded))
	// {	
		printf("%lld ", timestamp() - data->table->start_time);
		printf("%d %s\n", ph_id, str);
	// }
	pthread_mutex_unlock(&data->table->message);
}

int	write_error(char *str)
{
	int	len;
	
	len = 0;
	while (str[len])
		len++;
	write(2, "Error: ", 8);
	write(2, str, len);
	write(2, "\n", 1);
	return(-1);
}


long long	time_diff(long long past, long long pres)
{
	return (pres - past);
}

void	ft_sleep(long long time)
{
	while (timestamp() - time > 0)
	{
		usleep(300);
	}
	return ;
}

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
	while (table->nbr_ph > i++)
	{
		if (pthread_mutex_init(table->forks + i, NULL))
			return (-1);
	}
	if (pthread_mutex_init(&table->message, NULL))
		return (-1);
	return (0);
}

void	init_philos(t_data *data)
{
	int	i;

	i = 0;

	while (data->table->nbr_ph > i)
	{
		data->ph[i].ph_id = i + 1;
		data->ph[i].left_fork = &data->table->forks[i];
		data->ph[i].right_fork = &data->table->forks[(i + 1) % data->table->nbr_ph];
		data->ph[i].ate = 0;
		i++;
	}
	return ;
}

void	eating(t_data *data, t_ph *ph)
{
	// t_data	*data = ph->data;

	pthread_mutex_lock(ph->left_fork);
	ft_message(data, ph->ph_id, "has taken a left fork");
	pthread_mutex_lock(ph->right_fork);
	ft_message(data, ph->ph_id, "has taken a right fork");
	if (timestamp() - ph->t_last_meal > data->table->t_eat)
		pthread_mutex_lock(ph->right_fork);
	ph->t_last_meal = timestamp();
	ph->ate++;
	ft_message(data, ph->ph_id, "is eating");
	ft_sleep(ph->t_last_meal + data->table->t_eat);
	pthread_mutex_unlock(ph->left_fork);
	pthread_mutex_unlock(ph->right_fork);
}

void	*life(void *v_data)
{
	t_data *data = v_data;
	t_ph	*ph = data->ph + data->ind_cur;
	
	ph->t_last_meal = timestamp();
	printf("%s %d\n", "cheated", ph->ph_id);
	while (1)
	{
		eating(data, ph);
		ft_message(data, ph->ph_id, "is slepping");
		ft_sleep(timestamp() + data->table->t_sleep);
		ft_message(data, ph->ph_id, "is thinking");
	}
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
	// data->table->start_time = timestamp(); 
	// while (data->table->nbr_ph > i++)
	printf("%d\n", data->table->nbr_ph);
	while (i < data->table->nbr_ph)
	{
		data->ind_cur = i;
		if (pthread_create(&data->ph[i].thread_id, NULL, &life, data))
			return (-1);
		usleep(50);
		i++;
	}
	write(1, "allo\n", 5);
	pthread_join(data->ph[i - 1].thread_id, NULL);
	write(1, "poka\n", 5);
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	table;
	t_data	data;
	data.table = &table;

	// data.table = malloc(sizeof(*data.table));
	if (argc < 5 || argc > 6)
		return(write_error("Not enough arguments"));
	if (parcing(&table, argv))
		return(write_error("Incorrect_arguments"));
	if (init(&data))
		return(write_error("Init"));
	
	// printf("\n%d\n", data.ph[0].ph_id);
	// printf("%d\n", data.ph[1].ph_id);
	// printf("%d\n", data.ph[2].ph_id);
	// printf("%d\n", data.ph[3].ph_id);
	// printf("%d\n", data.ph[4].ph_id);
	// printf("lf%d\n", data.ph[4].left_fork);
	// printf("rf%d\n", data.ph[4].right_fork);
	return (0);
}

