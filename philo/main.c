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

	while (i < data->table->nbr_ph)
	{
		data->ph[i].ph_id = i + 1;
		data->ph[i].left_fork = &data->table->forks[i];
		data->ph[i].right_fork = &data->table->forks[(i + 1) % data->table->nbr_ph];
		data->ph[i].ate = 0;
		i++;
	}
	return ;
}

int	monitoring(t_data *data)
{
	int	i;
	long long	t = timestamp();
	
	while (1)
	{
		i = 0;
		while (i < data->table->nbr_ph)
		{
			// if (data->table->t_die < t - data->ph->t_last_meal)
			if (t - data->ph->t_last_meal > data->table->t_die)
			{
				// write(1, "jopka\n", 6);
				// printf("t_die %d\n", data->table->t_die);
				// printf("ttttt %lld\n", timestamp() - data->ph->t_last_meal);

				ft_message(data, data->ph->ph_id, "died");
				data->table->dieded = 1;
				
				return (1);
			}
			if (data->ph->ate == data->table->must_to_eat && data->table->all_ate != 0)
			{
				ft_message(data, data->ph->ph_id, "the end");
				return (1);
			}
			usleep (50);
			i++;
		}
	}
	return (0);
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
	while (1)
	{
		eating(data, ph);
		ft_message(data, ph->ph_id, "is slepping");
		ft_sleep(timestamp() + data->table->t_sleep);
		ft_message(data, ph->ph_id, "is thinking");
	}
}

int	mem_free(t_data *data)
{	
	int	i;

	i = 0;
	pthread_mutex_unlock(data->ph->right_fork);

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

int	creating_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->table->nbr_ph)
	{
		data->ind_cur = i;
		data->table->start_time = timestamp();
		if (pthread_create(&data->ph[i].thread_id, NULL, &life, data))
			return (-1);
		usleep(50);
		i++;
	}
	return (0);
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

int	main(int argc, char **argv)
{
	t_table	table;
	t_data	data;
	data.table = &table;

	if (argc < 5 || argc > 6)
		return(write_error("Not enough arguments"));
	if (parcing(&table, argv))
		return(write_error("Incorrect_arguments"));
	if (init(&data))
		return(write_error("Init"));
	if (creating_philos(&data))
		return(write_error("Create pthreads"));
	if (monitoring(&data))
		return(1);

	mem_free(&data);

	return (0);
}

