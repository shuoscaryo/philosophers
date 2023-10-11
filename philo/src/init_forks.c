/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orudek <orudek@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:26:38 by orudek            #+#    #+#             */
/*   Updated: 2023/10/11 14:30:20 by orudek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	free_mutex(t_mtx *mutex, int len)
{
	int	i;

	i = -1;
	while (++i < len)
		pthread_mutex_destroy(&mutex[i]);
	free(mutex);
}

int	init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(t_mtx) * data->shared.philos_num);
	if (!data->forks)
		return (0);
	i = -1;
	while (++i < data->shared.philos_num)
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (free_mutex(data->forks, i), 0);
	return (1);
}
