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

#include "philo_one.h"

long long	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return((t.tv_sec * 1000) + (t.tv_usec /1000));
}

long long	time_diff(long long past, long long pres)
{
	return (pres - past);
}

void	smart_sleep(long long time, t_data *data)
{
	long long i;

	i = timestamp();
	while (!(data->dieded))
	{
		if (time_diff(i, timestamp()) >= time)
			break ;
		usleep(50);
	}
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
	return(1);
}

void	ft_message(t_data *data, int ph_id, char *str)
{
	pthread_mutex_lock(&data->message);
	printf("%lld ", timestamp() - data->start_time);
	printf("%d %s\n", ph_id, str);
	if (!data->dieded)
		pthread_mutex_unlock(&data->message);
}

void	death_checker(t_data *data, t_ph *ph)
{
	int	i;

	while(!(data->all_ate))
	{	
		i = 0;
		while (data->nbr_ph > i && !(data->dieded))
		{
			if (time_diff(ph[i].t_last_meal, timestamp()) > data->time_die)
			{
				data->dieded = 1;
				ft_message(data, i, "died");
			}
			usleep(100);
			i++;
		}
		if(data->dieded)
		{	
			break ;
		}
		i = 0;
		while (data->nbr_times_ph_must_eat != -1 && data->nbr_ph > i && data->time_die)
			i++;
		if (i == data->nbr_ph)
			data->all_ate = 1;
	}
}


void	ph_eat(t_ph *ph)
{
	t_data	*data = ph->data;

	pthread_mutex_lock(&data->forks[ph->left_fork]);
	ft_message(data, ph->ph_id, "has taken a fork");
	pthread_mutex_lock(&data->forks[ph->right_fork]);
	ft_message(data, ph->ph_id, "has taken a fork");
	ft_message(data, ph->ph_id, "is eating");
	ph->t_last_meal = timestamp();
	smart_sleep(data->time_eat, data);
	(ph->ate)++;

	pthread_mutex_unlock(&data->forks[ph->left_fork]);
	pthread_mutex_unlock(&data->forks[ph->right_fork]);
}

void	*ft_thread(void *void_philo)
{
	t_ph	*ph =(void *)void_philo;
	t_data	*data = ph->data;

	if (ph->ph_id % 2)
		usleep(15000);
	while(!(data->dieded))
	{
		ph_eat(ph);
		if (data->all_ate)
			break ;
		ft_message(data, ph->ph_id, "is slepping");
		smart_sleep(data->time_sleep, data);
		ft_message(data, ph->ph_id, "is thinking");
	}
	return (NULL);
}

int	create_mutex(t_data *data)
{
	int	i;
	
	i = 0;
	while (data->nbr_ph > i++)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL))
			return (write_error("mutex"));//
	}
	if (pthread_mutex_init(&data->message, NULL))
		return(write_error("write-mutex"));//
	return (0);
}

int	create_philo(t_data *data)
{
	int	i;

	i = 0;
	data->start_time = timestamp();
	while (data->nbr_ph > i++)
	{
		data->ph[i].ph_id = i;
		data->ph[i].left_fork = i;
		data->ph[i].right_fork = (i + 1) % data->nbr_ph;
		data->ph[i].t_last_meal = 0;
		data->ph[i].data = data;
		if (pthread_create(&data->ph[i].thread_id, NULL, ft_thread, &(data->ph[i])) != 0)
			return (1);
		data->ph[i].t_last_meal = timestamp();
	}
	death_checker(data, data->ph);
	i = 0;
	while (data->nbr_ph > i++)
	{
		if (pthread_join((data->ph[i].thread_id), NULL) != 0)
			return (1);
	}
	while (data->nbr_ph > i++)
	{
		pthread_mutex_destroy(&data->forks[i]);
	}
	pthread_mutex_destroy(&data->message);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	(void)argc;

	if (parcing(&data, argv))
		return(write_error("Incorrect_arguments"));
	data.ph = malloc(sizeof(*data.ph) * data.nbr_ph);
	data.forks = malloc(sizeof(*data.ph) * data.nbr_ph);
	if (create_mutex(&data))
		return(write_error("create forks"));
	if (create_philo(&data))
		return(write_error("create philo"));

	
	return (0);
}

/*	- Каждый философ - отдельный поток
*	- операции "захват/освобождения" вилки реализуются через мьютексы
*	- захват вилок происходит иерархически
*	
*/	