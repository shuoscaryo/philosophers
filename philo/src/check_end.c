/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_end.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orudek <orudek@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:28:35 by orudek            #+#    #+#             */
/*   Updated: 2023/10/13 19:28:31 by orudek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	set_end(t_data *data)
{
	pthread_mutex_lock(&data->shared.shared_mtx);
	data->shared.end = 1;
	pthread_mutex_unlock(&data->shared.shared_mtx);	
	return (1);
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
		pthread_mutex_lock(&data->philos[i].philo_mtx); //NOTE mirar porque esto no se puede quitar
		time = get_time() - data->philos[i].last_meal_time;
		if (data->philos[i].meals_remaining)
			all_eaten = 0;
		pthread_mutex_unlock(&data->philos[i].philo_mtx);		
		if (time > data->shared.death_time)
		{
			pthread_mutex_lock(&data->shared.shared_mtx);
			printf("%lu %d has died\n", time , data->philos[i].id);
			data->shared.end = 1;
			pthread_mutex_unlock(&data->shared.shared_mtx);		
			return (1);
		}	
	}
	if (all_eaten)
		return (set_end(data));
	return (0);
}
