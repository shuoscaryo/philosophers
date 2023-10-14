/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orudek <orudek@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:28:35 by orudek            #+#    #+#             */
/*   Updated: 2023/10/14 16:36:39 by orudek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	set_end(t_shared *shared)
{
	pthread_mutex_lock(&shared->shared_mtx);
	shared->end = 1;
	pthread_mutex_unlock(&shared->shared_mtx);
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
		if (time > data->shared.death_time)
		{
			printf("%lu %d %s\n", get_time() - data->shared.start_time, i, DEAD_MSG);
			data->shared.end = 1;
			pthread_mutex_unlock(&data->shared.shared_mtx);
			return (1);
		}	
		pthread_mutex_unlock(&data->shared.shared_mtx);
	}
	if (all_eaten)
		return (set_end(&data->shared), 1);
	return (0);
}
