/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shared.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orudek <orudek@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 22:13:24 by orudek            #+#    #+#             */
/*   Updated: 2023/10/11 14:10:46 by orudek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_atoi(char *str)
{
	int out;

	out = 0;
	if (*str == '+')
		str++;
	while (*str)
	{
		out = out * 10 + *str - '0';
		str++;
	}
	return (out);
}

static int	inputs_ok(char **argv)
{
	int			i;
	long long	num;

	while (*++argv)
	{
		i = 0;
		if (**argv == '-')
			return (0);
		if (**argv == '+')
			i = 1;
		num = 0;
		while ((*argv)[i])
		{
			if ((*argv)[i] < '0' || (*argv)[i] > '9')
				return (0);
			num = num * 10 + (*argv)[i] - '0';
			if (num > MAX_INT)
				return (0);
			i++;
		}
	}
	return (1);
}

int	init_shared(t_shared *shared, int argc, char **argv)
{
	if (!inputs_ok(argv))
		return (0);
	shared->start_time = get_time();
	shared->eat_time = ft_atoi(argv[3]);
	shared->sleep_time = ft_atoi(argv[4]);
	shared->death_time = ft_atoi(argv[2]);
	if (argc == 6)
		shared->meals_num = ft_atoi(argv[5]);
	else
		shared->meals_num = -1;
	shared->philos_num = ft_atoi(argv[1]);
	shared->end = 0;
	if (pthread_mutex_init(&shared->write_mtx, NULL))
		return (0);
	return (1);
}
