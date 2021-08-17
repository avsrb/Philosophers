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

void	ft_putchar(char c)
{
	write (1, &c, 1);
}

static void	ft_putnbr(int n)
{
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
	}
	else if (n < 0)
	{		
		write(1, "-", 1);
		ft_putnbr(-n);
	}
	else if (n > 9)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
		ft_putchar(n + '0');
}

int	monitoring(t_data *data)
{
	int	i;
	
	while (1)
	{
		i = 0;
		while (i < data->table->nbr_ph)
		{
			if (timestamp() - data->ph[i].t_last_meal > data->table->t_die)
			{
				ft_message(data, data->ph->ph_id, "died");
				data->table->dieded = 1;
				return (1);
			}
			if (data->table->all_ate % (data->table->must_to_eat * data->table->nbr_ph) == 0 && 
					data->table->all_ate != 0)
			{
				ft_message(data, data->ph->ph_id, "the end");
				return (1);
			}
			usleep (100);
			i++;
		}
	}
	return (0);
}

void	eating(t_data *data, t_ph *ph)
{
	pthread_mutex_lock(&(data->table->forks[ph->left_fork]));
	ft_message(data, ph->ph_id, "has taken a left fork");
	pthread_mutex_lock(&(data->table->forks[ph->right_fork]));
	ft_message(data, ph->ph_id, "has taken a right fork");
	////// if (timestamp() - ph->t_last_meal > data->table->t_eat)
	////// {	
	////// 	pthread_mutex_lock(&(data->table->forks[ph->left_fork]));
	////// }
	ph->t_last_meal = timestamp();
	ph->ate++;
	data->table->all_ate++;
	// if (ph->ate == data->table->must_to_eat)
	// if (data->ph[ph->ph_id - 1].ate == data->table->must_to_eat)
	// {
	// 	data->table->all_ate += 1;
	// 	ft_putnbr(data->ph[ph->ph_id-1].ate);
	// 	write(1, "\n", 1);
	// }
	ft_message(data, ph->ph_id, "is eating");
	ft_sleep(data->table->t_eat);
	pthread_mutex_unlock(&(data->table->forks[ph->left_fork]));
	pthread_mutex_unlock(&(data->table->forks[ph->right_fork]));
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
		ft_sleep(data->table->t_sleep);
		ft_message(data, ph->ph_id, "is thinking");
	}
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

int	creating_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->table->nbr_ph)
	{
		data->ind_cur = i;
		data->table->start_time = timestamp();
		if (pthread_create(&data->ph[i].thread_id, NULL, life, data))
			return (-1);
		usleep(50);
		i++;
	}
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
	monitoring(&data);
	mem_free(&data);

	

	return (0);
}

