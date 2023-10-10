/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_mutex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orudek <orudek@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 16:59:47 by orudek            #+#    #+#             */
/*   Updated: 2023/10/10 20:25:43 by orudek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	create_mutex(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(t_mtx) * data->philos_num);
	if (!data->forks)
		return (0);
	i = -1;
	while (++i < data->philos_num)
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (free_mutex(data->forks, i));
	if (pthread_mutex_init(&data->write_mtx, NULL))
		return (free_mutex(data->forks, i));
	return (1);
}
