/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orudek <orudek@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:37:58 by orudek            #+#    #+#             */
/*   Updated: 2023/10/14 15:39:08 by orudek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


void	free_data(t_data *data) //NOTE do this
{
	pthread_mutex_destroy(&data->shared.shared_mtx);
	//free_(data->forks, data->philos_num);
	free(data->forks);
	free(data->threads);
	free(data->philos);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (!init_data(&data, argc, argv))
		return (1);
	while (!check_end(&data))
		usleep(SLEEP_TICKS);
	while (i < data.shared.philos_num)
		pthread_join(data.threads[i++],NULL);
	free_data(&data);
	return (0);
}
