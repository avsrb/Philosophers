/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshmelly <mshmelly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/18 17:46:00 by mshmelly          #+#    #+#             */
/*   Updated: 2021/08/23 00:50:33 by mshmelly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((*(s1 + i) || *(s2 + i)))
	{	
		if (*(s1 + i) != *(s2 + i))
			return (*(unsigned char *)(s1 + i) - *(unsigned char *)(s2 + i));
		i++;
	}
	return (0);
}

static void	ft_putchar(char c)
{
	write (1, &c, 1);
}

static void	ft_putnbr_ll(long long n)
{
	if (n == -9223372036854775807)
	{
		write(1, "−9223372036854775807", 23);
	}
	else if (n < 0)
	{		
		write(1, "-", 1);
		ft_putnbr_ll(-n);
	}
	else if (n > 9)
	{
		ft_putnbr_ll(n / 10);
		ft_putnbr_ll(n % 10);
	}
	else
		ft_putchar(n + '0');
}

void	ft_message(t_data *data, int ph_id, char *str)
{
	int			len;
	uint64_t	tt;

	len = 0;
	while (str[len])
		len++;
	tt = timestamp() - data->table->start_time;
	if (tt >= 0)
	{
		pthread_mutex_lock(&data->table->message);
		ft_putnbr_ll(tt);
		ft_putchar(' ');
		ft_putnbr_ll(ph_id);
		ft_putchar(' ');
		write(1, str, len);
		ft_putchar('\n');
	}
	if (ft_strcmp(str, DIED))
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
	return (-1);
}
