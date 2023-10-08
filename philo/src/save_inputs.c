/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_inputs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orudek <orudek@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 22:13:24 by orudek            #+#    #+#             */
/*   Updated: 2023/10/06 22:13:50 by orudek           ###   ########.fr       */
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

int	save_inputs(t_data *data, int argc, char **argv)
{
	if (!inputs_ok(argv))
		return (0);
	data->num_of_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->num_of_meals = ft_atoi(argv[5]);
	else
		data->num_of_meals = -1;
	return (1);
}
