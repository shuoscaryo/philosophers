/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orudek <orudek@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:26:38 by orudek            #+#    #+#             */
/*   Updated: 2023/10/11 15:58:12 by orudek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	free_forks(t_mtx *forks, int len)
{
	int	i;

	i = -1;
	while (++i < len)
		pthread_mutex_destroy(&forks[i]);
	free(forks);
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
			return (free_forks(data->forks, i), 0);
	return (1);
}
