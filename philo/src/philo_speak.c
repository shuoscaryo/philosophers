/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_speak.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orudek <orudek@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:38:55 by orudek            #+#    #+#             */
/*   Updated: 2023/10/13 17:39:15 by orudek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_speak(t_philo *philo, char *msg)
{
	t_ulong	time;

	if (philo->shared->end)
		return ;
	time = get_time() - philo->shared->start_time;
	pthread_mutex_lock(&philo->shared->shared_mtx);
	printf("%lu %d %s\n", time , philo->id, msg);
	pthread_mutex_unlock(&philo->shared->shared_mtx);
}
