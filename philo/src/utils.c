/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orudek <orudek@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:38:55 by orudek            #+#    #+#             */
/*   Updated: 2023/10/14 15:49:34 by orudek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_ulong	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	sleep_ms(t_ulong ms)
{
	//usleep(ms * 1000);
	t_ulong	start;

	start = get_time();
	while (ms > get_time() - start)
		usleep(SLEEP_TICKS); 
}

void	philo_speak(t_philo *philo, char *msg)
{
	t_ulong	time;

	pthread_mutex_lock(&philo->shared->shared_mtx);
	if (!philo->shared->end)
	{
		time = get_time() - philo->shared->start_time;
		printf("%lu %d %s\n", time , philo->id, msg);
	}
	pthread_mutex_unlock(&philo->shared->shared_mtx);
}
