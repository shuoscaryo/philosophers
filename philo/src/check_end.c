/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orudek <orudek@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:28:35 by orudek            #+#    #+#             */
/*   Updated: 2023/10/14 21:14:29 by orudek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	set_end(t_shared *shared)
{
	pthread_mutex_lock(&shared->shared_mtx);
	shared->end = 1;
	pthread_mutex_unlock(&shared->shared_mtx);
}

int	check_death(t_data *data, t_ulong time, int i)
{
	if (time > data->shared.death_time)
	{
		printf("%lu %d %s\n", get_time() - data->shared.start_time,
			i + 1, DEAD_MSG);
		data->shared.end = 1;
		return (1);
	}
	return (0);
}

int	check_end(t_data *data)
{
	int		i;
	t_ulong	time;
	int		all_eaten;

	i = -1;
	all_eaten = 1;
	while (++i < data->shared.philos_num)
	{
		pthread_mutex_lock(&data->shared.shared_mtx);
		pthread_mutex_lock(&data->philos[i].philo_mtx);
		time = get_time() - data->philos[i].last_meal_time;
		if (data->philos[i].meals_remaining != 0)
			all_eaten = 0;
		pthread_mutex_unlock(&data->philos[i].philo_mtx);
		if (check_death(data, time, i))
			return (pthread_mutex_unlock(&data->shared.shared_mtx), 1);
		pthread_mutex_unlock(&data->shared.shared_mtx);
	}
	if (all_eaten)
		return (set_end(&data->shared), 1);
	return (0);
}
