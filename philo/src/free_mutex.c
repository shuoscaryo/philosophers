/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mutex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orudek <orudek@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 17:00:43 by orudek            #+#    #+#             */
/*   Updated: 2023/10/08 17:01:22 by orudek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	free_mutex(pthread_mutex_t *mutex, int len)
{
	int	i;

	i = -1;
	while (++i < len)
		pthread_mutex_destroy(&mutex[i]);
	free(mutex);
	return (0);
}
