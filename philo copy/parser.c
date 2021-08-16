/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshmelly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 13:35:19 by mshmelly          #+#    #+#             */
/*   Updated: 2021/08/09 13:35:22 by mshmelly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_atoi_int(const char *str)
{
	int			negative;
	int			i;
	long		convert;

	negative = 1;
	i = 0;
	convert = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			negative = -negative;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		convert = convert * 10 + (str[i++] - '0') * negative;
	if (convert > 2147483647 || convert < -2147483648)
		write_error("Integer overflow");
	return (convert);
}

int	parcing(t_table *data, char **argv)
{
	data->nbr_ph = ft_atoi_int(argv[1]);
	data->time_die = ft_atoi_int(argv[2]);
	data->time_eat = ft_atoi_int(argv[3]);
	data->time_sleep = ft_atoi_int(argv[4]);
	data->dieded = 0;
	data->all_ate = 0;
	if(argv[5])
	{
		data->nbr_times_ph_must_eat = ft_atoi_int(argv[5]);
		if (data->nbr_times_ph_must_eat <= 0)
			return (1);
	}
	else
		data->nbr_times_ph_must_eat = -8;
	if(data->nbr_ph < 1 || data->time_die < 1 || data->time_eat < 1
		|| data->time_sleep < 1 || data->nbr_ph >= 200)
		return (1);
	return (0);
}