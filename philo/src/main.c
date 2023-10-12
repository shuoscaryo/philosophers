/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orudek <orudek@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:37:58 by orudek            #+#    #+#             */
/*   Updated: 2023/10/13 01:15:31 by orudek           ###   ########.fr       */
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

void	philo_init(t_philo *philo)
{
	if (philo->id % 2 == 0) // move this to create philo
		usleep(philo->shared->eat_time / 2);
		//check death after this
	pthread_mutex_lock(&philo->philo_mtx);
	philo->last_meal_time = get_time();
	pthread_mutex_unlock(&philo->philo_mtx);
}

void	philo_speak(t_philo *philo, int MSG)
{
	t_ulong	time;

	if (philo->shared->end)
		return ;
	time = get_time() - philo->shared->start_time;
	pthread_mutex_lock(&philo->shared->shared_mtx);
	if (MSG == TAKE_FORK_MSG)
		printf("%lu %d has taken a fork\n", time , philo->id);
	else if (MSG == EATING_MSG)
		printf("%lu %d is eating\n", time , philo->id);
	else if (MSG == SLEEPING_MSG)
		printf("%lu %d is sleeping\n", time , philo->id);
	else if (MSG == THINKING_MSG)
		printf("%lu %d is thinking\n", time , philo->id);
	else if (MSG == DEAD_MSG)
		printf("%lu %d has died\n", time , philo->id);
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
	philo_init(philo);
	while (!philo->shared->end)
	{	
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
	int		all_eaten;

	if (!init_data(&data, argc, argv))
		return (1);
	while (!data.shared.end)
	{
		i = -1;
		all_eaten = 1;
		while (++i < data.shared.philos_num)
		{
			pthread_mutex_lock(&data.philos[i].philo_mtx);
			if (get_time() - data.philos[i].last_meal_time
					> data.shared.death_time)
			{
				pthread_mutex_lock(&data.shared.shared_mtx);
				printf("%d DIED\n",i + 1);
				data.shared.end = 1;
				pthread_mutex_unlock(&data.shared.shared_mtx);
				break ;
			}
			if (data.philos[i].meals_remaining)
				all_eaten = 0;
			pthread_mutex_unlock(&data.philos[i].philo_mtx);
		}
		if (data.shared.end == 0 && all_eaten)
		{
			pthread_mutex_lock(&data.shared.shared_mtx);
			printf("EVERYONE HAS EATEN\n");
			pthread_mutex_unlock(&data.shared.shared_mtx);
			pthread_mutex_lock(&data.shared.shared_mtx);
			data.shared.end = 1;
			pthread_mutex_unlock(&data.shared.shared_mtx);
		}
	}
	while (i < data.shared.philos_num)
		pthread_join(data.threads[i++],NULL);
	free_data(&data);
	return (0);
}
