/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orudek <orudek@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:21:13 by orudek            #+#    #+#             */
/*   Updated: 2023/10/13 19:30:39 by orudek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	philo_speak(philo, TAKE_FORK_MSG);
	pthread_mutex_lock(philo->right_fork);
	philo_speak(philo, TAKE_FORK_MSG);
	philo_speak(philo, EATING_MSG);
	pthread_mutex_lock(&philo->philo_mtx);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->philo_mtx);
	sleep_ms(philo->shared->eat_time);
	pthread_mutex_lock(&philo->philo_mtx);
	if (philo->meals_remaining != -1)
		philo->meals_remaining--;
	pthread_mutex_unlock(&philo->philo_mtx);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

static void	philo_sleep(t_philo *philo)
{
	philo_speak(philo, SLEEPING_MSG);
	sleep_ms(philo->shared->sleep_time);
}

void	*philo_routine(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	if (philo->meals_remaining == 0)
		return (NULL) ;
	philo_speak(philo, THINKING_MSG);
	if (philo->id % 2 == 0)
		sleep_ms(philo->shared->eat_time / 10);
	while (!get_end(philo->shared))
	{	
		philo_eat(philo);
		//if (!get_end(philo->shared))
		//	return (NULL);
		philo_sleep(philo);
		//if (!get_end(philo->shared))
	//		return (NULL);
		philo_speak(philo, THINKING_MSG);
	}
	return (NULL);
}