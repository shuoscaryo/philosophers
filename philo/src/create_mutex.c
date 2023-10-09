/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_mutex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orudek <orudek@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 16:59:47 by orudek            #+#    #+#             */
/*   Updated: 2023/10/08 19:40:24 by orudek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	create_mutex(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(t_mtx) * data->num_of_philos);
	if (!data->forks)
		return (0);
	i = -1;
	while (++i < data->num_of_philos)
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (free_mutex(data->forks, i));
	if (pthread_mutex_init(&data->write_lock, NULL))
		return (free_mutex(data->forks, i));
	return (1);
}
