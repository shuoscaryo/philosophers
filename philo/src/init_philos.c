/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orudek <orudek@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 23:39:19 by orudek            #+#    #+#             */
/*   Updated: 2023/10/14 20:02:07 by orudek           ###   ########.fr       */
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

static void	join_threads(t_data *data, int num)
{
	int	i;

	pthread_mutex_lock(&data->shared.shared_mtx);
	data->shared.end = 1;
	pthread_mutex_unlock(&data->shared.shared_mtx);
	i = -1;
	while (++i < num)
		pthread_join(data->threads[i], NULL);
}

static int	init_threads(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->shared.philos_num)
	{
		if (pthread_create(&data->threads[i],
				NULL, philo_routine, &data->philos[i]))
		{
			join_threads(data, i);
			free_philos(data, data->shared.philos_num);
			return (0);
		}
	}
	return (1);
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
		data->philos[i].fork[0] = &data->forks[i];
		data->philos[i].fork[1]
			= &data->forks[(i + 1) % data->shared.philos_num];
		data->philos[i].shared = &data->shared;
		if (pthread_mutex_init(&data->philos[i].philo_mtx, NULL))
			return (free_philos(data, i), 0);
	}
	return (init_threads(data));
}
