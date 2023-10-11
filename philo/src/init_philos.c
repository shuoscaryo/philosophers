/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orudek <orudek@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 23:39:19 by orudek            #+#    #+#             */
/*   Updated: 2023/10/11 16:11:55 by orudek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	free_philos(t_data *data, int len)
{
	int	i;

	i = -1;
	while (++i < len)
		pthread_mutex_destroy(&data->philos[i].philo_mtx);
	free(data->philos);
	free(data->threads);
}
static int init_threads(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->shared.philos_num)
	{
		if (pthread_create(&data->threads[i], NULL, philo_routine))
	}
}

int	init_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->shared.philos_num);
	if (!data->philos)
		return (0);
	data->threads = malloc(sizeof(pthread_t) * data->shared.philos_num);
	if (!data->threads)
		return (free(data->philos), 0);
	i = -1;
	while (++i < data->shared.philos_num)
	{
		data->philos[i].id = i + 1;
		data->philos[i].last_meal_time = data->shared.start_time;
		data->philos[i].meals_remaining = data->shared.meals_num;
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork
			= &data->forks[(i + 1) % data->shared.philos_num];
		data->philos[i].shared = &data->shared;
		if (pthread_mutex_init(&data->philos[i].philo_mtx, NULL))
			return (free_philos(data, i), 0);
	}
	return (init_threads(data));
}
