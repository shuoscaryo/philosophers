/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orudek <orudek@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:21:13 by orudek            #+#    #+#             */
/*   Updated: 2023/10/16 17:11:15 by orudek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->fork[philo->id % 2]);
	philo_speak(philo, TAKE_FORK_MSG);
	pthread_mutex_lock(philo->fork[!(philo->id % 2)]);
	philo_speak(philo, TAKE_FORK_MSG);
	pthread_mutex_lock(&philo->philo_mtx);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->philo_mtx);
	philo_speak(philo, EATING_MSG);
	sleep_ms(philo->shared->eat_time);
	pthread_mutex_lock(&philo->philo_mtx);
	if (philo->meals_remaining > 0)
		philo->meals_remaining--;
	pthread_mutex_unlock(&philo->philo_mtx);
	pthread_mutex_unlock(philo->fork[!(philo->id % 2)]);
	pthread_mutex_unlock(philo->fork[philo->id % 2]);
}

static void	philo_sleep(t_philo *philo)
{
	philo_speak(philo, SLEEPING_MSG);
	sleep_ms(philo->shared->sleep_time);
}

static int	get_end(t_shared *shared)
{
	int	end;

	pthread_mutex_lock(&shared->shared_mtx);
	end = shared->end;
	pthread_mutex_unlock(&shared->shared_mtx);
	return (end);
}

static void	synchronize(t_philo *philo)
{
	t_ulong	eat_t;
	t_ulong	sleep_t;

	if (philo->shared->philos_num % 2 == 0)
		return ;
	eat_t = philo->shared->eat_time;
	sleep_t = philo->shared->sleep_time;
	if (eat_t * 3 / 2 > sleep_t)
		sleep_ms(eat_t * 3 / 2 - sleep_t);
}

void	*philo_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->meals_remaining == 0)
		return (NULL);
	philo_speak(philo, THINKING_MSG);
	if (philo->shared->philos_num == 1)
	{
		philo_speak(philo, TAKE_FORK_MSG);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		sleep_ms(philo->shared->eat_time / 2);
	if (philo->shared->philos_num % 2 == 1
		&& philo->id == philo->shared->philos_num)
		sleep_ms(philo->shared->eat_time * 3 / 2);
	while (!get_end(philo->shared))
	{	
		philo_eat(philo);
		philo_sleep(philo);
		philo_speak(philo, THINKING_MSG);
		synchronize(philo);
	}
	return (NULL);
}
