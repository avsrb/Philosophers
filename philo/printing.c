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

static void	ft_putnbr_ll(long long n)
{
	if (n == -9223372036854775807)
	{
		write(1, "−9223372036854775807", 23);
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

void	ft_message(t_data *data, int ph_id, char *str)
{
	pthread_mutex_lock(&data->table->message);
	int	len;

	len = 0;
	while (str[len])
		len++;
	if(!(data->table->dieded))
	{	
		ft_putnbr_ll(timestamp() - data->table->start_time);
		// printf("%d %s\n", ph_id, len);
		write(1, " ", 1);
		ft_putnbr(ph_id);
		write(1, " ", 1);
		write(1, str, len);
		write(1, "\n", 1);
	}
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