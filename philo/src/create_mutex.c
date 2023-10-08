/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_mutex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orudek <orudek@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 16:59:47 by orudek            #+#    #+#             */
/*   Updated: 2023/10/08 17:00:03 by orudek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	create_mutex(t_data *data)
{
	int	i;
	int	error;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philos);
	if (!data->forks)
		return (NULL);
	i = -1;
	while (++i < data->num_of_philos)
	{
		error = pthread_mutex_init(&data->forks[i], NULL);
		if (error)
			return (free_mutex(data->forks, i));
	}
	error = pthread_mutex_init(&data->write_lock, NULL);
	if (error)
		return (free_mutex(data->forks, i));
}
