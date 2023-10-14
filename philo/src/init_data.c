/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orudek <orudek@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:15:07 by orudek            #+#    #+#             */
/*   Updated: 2023/10/14 16:11:29 by orudek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	free_shared(t_shared *shared)
{
	pthread_mutex_destroy(&shared->shared_mtx);
}

static void	free_forks(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->shared.philos_num)
		pthread_mutex_destroy(&data->forks[i]);
	free(data->forks);
}

int	init_data(t_data *data, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (0);
	if (!init_shared(&data->shared, argc, argv))
		return (0);
	if (!init_forks(data))
		return (free_shared(&data->shared), 0);
	if (!init_philos(data))
		return (free_shared(&data->shared), free_forks(data), 0);
	return (1);
}
