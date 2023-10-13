/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orudek <orudek@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:37:58 by orudek            #+#    #+#             */
/*   Updated: 2023/10/13 17:25:18 by orudek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void print_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->shared->shared_mtx);
	printf("Philo data:\n");
	printf("\tid: %d\n",philo->id);
	printf("\tlast_meal_time: %lu\n",philo->last_meal_time);
	printf("\tmeals_remaining: %d\n",philo->meals_remaining);
	printf("\tleft_fork: (%p)\n", philo->left_fork);
	printf("\tright_fork: (%p)\n", philo->right_fork);
	printf("\tphilo_mtx (%p)\n", &philo->philo_mtx);
	printf("\tshared (%p)\n", philo->shared);
	pthread_mutex_unlock(&philo->shared->shared_mtx);
}

t_ulong	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	sleep_ms(t_ulong ms)
{
	t_ulong	start;

	start = get_time();
	while (ms > get_time() - start)
		usleep(SLEEP_TICKS);
}

void	free_data(t_data *data)
{
	pthread_mutex_destroy(&data->shared.shared_mtx);
	//free_(data->forks, data->philos_num);
	free(data->forks);
	free(data->threads);
	free(data->philos);
}

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

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	philo_speak(philo, TAKE_FORK_MSG);
	pthread_mutex_lock(philo->right_fork);
	philo_speak(philo, TAKE_FORK_MSG);
	philo_speak(philo, EATING_MSG);
	pthread_mutex_lock(&philo->philo_mtx);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->philo_mtx);
	if (philo->meals_remaining != -1)
		philo->meals_remaining--;
	sleep_ms(philo->shared->eat_time);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_sleep(t_philo *philo)
{
	philo_speak(philo, SLEEPING_MSG);
	sleep_ms(philo->shared->sleep_time);
}

void	*philo_routine(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	philo_speak(philo, THINKING_MSG);
	if (philo->id % 2 == 0)
		sleep_ms(philo->shared->eat_time / 2);
	while (!philo->shared->end)
	{	
		philo_speak(philo, "NEW CYCLE");
		if (philo->meals_remaining == 0)
			break ;
		philo_speak(philo, THINKING_MSG);
		if (philo->shared->end)
			return (NULL);
		philo_eat(philo);
		if (philo->shared->end)
			return (NULL);
		philo_sleep(philo);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (!init_data(&data, argc, argv))
		return (1);
	while (!check_end(&data))
		;
	while (i < data.shared.philos_num)
		pthread_join(data.threads[i++],NULL);
	free_data(&data);
	return (0);
}
