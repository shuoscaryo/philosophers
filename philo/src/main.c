/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orudek <orudek@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:37:58 by orudek            #+#    #+#             */
/*   Updated: 2023/10/11 14:15:17 by orudek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void print_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->write_mtx);
	printf("Philo data:\n");
	printf("\tid: %d\n",philo->id);
	printf("\tstate: %d\n",philo->state);
	printf("\tlast_meal_time: %lu\n",philo->last_meal_time);
	printf("\tmeals_remaining: %d\n",philo->meals_remaining);
	printf("\ttime_to_eat: %lu\n",philo->time_to_eat);
	printf("\ttime_to_sleep: %lu\n",philo->time_to_sleep);
	printf("\tleft_fork: (%p)\n", philo->left_fork);
	printf("\tright_fork: (%p)\n", philo->right_fork);
	printf("\twrite_mtx: (%p)\n", philo->write_mtx);
	pthread_mutex_unlock(philo->write_mtx);
}

t_ulong	get_time(void)
{
	struct timeval time;

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
	pthread_mutex_destroy(&data->write_mtx);
	free_mutex(data->forks, data->philos_num);
	free(data->philos);
}

void	philo_init(t_philo *philo)
{
	if (philo->id % 2 == 0)
		usleep(philo->time_to_eat / 2);
	pthread_mutex_lock(&philo->philo_mtx);
	philo->last_meal_time = get_time();
	philo->state = 1;
	pthread_mutex_unlock(&philo->philo_mtx);
}

void	philo_speak(t_philo *philo, int MSG)
{
	t_ulong	time;

	time = get_time() - philo->start_time;
	pthread_mutex_lock(philo->write_mtx);
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
	pthread_mutex_unlock(philo->write_mtx);
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
	sleep_ms(philo->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_sleep(t_philo *philo)
{
	philo_speak(philo, SLEEPING_MSG);
	sleep_ms(philo->time_to_sleep);
}

void	*philo_routine(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	philo_init(philo);
	while (1)
	{
		if (philo->meals_remaining == 0)
			break ;
		philo_speak(philo, THINKING_MSG);
		philo_eat(philo);
		philo_sleep(philo);
	}
	return (NULL);
}

int	philo_dead(t_data *data)
{
	int	i;
	t_ulong	time;

	i = -1;
	time = get_time();	
	while (++i < data->philos_num)
	{
		pthread_mutex_lock(&data->philos[i].philo_mtx);
		if (time - data->philos[i].last_meal_time > data->time_to_die)
			return (1);
		pthread_mutex_unlock(&data->philos[i].philo_mtx);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (!init_data(&data, argc, argv))
		return (1);
	if (argc != 5 && argc != 6)
		return (1);
	if (!create_mutex(&data))
		return (1);
	if (!create_philos(&data))
	3	return (free_mutex(data.forks, data.philos_num), pthread_mutex_destroy(&data.write_mtx));
	i = -1;
	while (++i < data.philos_num)
		if (pthread_create(&data.threads[i], NULL, philo_routine, &data.philos[i]))
			return (free_data(&data), 1);
	i = 0;
	while (i < data.philos_num)
		pthread_join(data.threads[i++],NULL);
	return (0);
}
