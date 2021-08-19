/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshmelly <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 13:35:19 by mshmelly          #+#    #+#             */
/*   Updated: 2021/08/18 17:45:45 by mshmelly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

int	parcing(t_table *table, char **argv)
{
	table->nbr_ph = ft_atoi_int(argv[1]);
	table->t_die = ft_atoi_int(argv[2]);
	table->t_eat = ft_atoi_int(argv[3]);
	table->t_sleep = ft_atoi_int(argv[4]);
	table->all_ate = 0;
	if (argv[5])
	{
		table->must_to_eat = ft_atoi_int(argv[5]);
		if (table->must_to_eat <= 0)
			return (1);
	}
	else
		table->must_to_eat = INT_MAX;
	if (table->nbr_ph <= 0 || table->t_die < 0 || table->t_eat < 0
		|| table->t_sleep < 0 || table->nbr_ph > 200)
		return (1);
	return (0);
}
