/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orudek <orudek@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:15:07 by orudek            #+#    #+#             */
/*   Updated: 2023/10/11 14:26:26 by orudek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_data(t_data *data, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (0);
	if (!init_shared(&data->shared, argc, argv))
		return (0);
	if (!init_forks(data))
		return (pthread_mutex_destroy(&data->shared.write_mtx), 0);
	if (!init_philos(data))
		return (0);
	return (1);
}
