/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orudek <orudek@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:37:58 by orudek            #+#    #+#             */
/*   Updated: 2023/10/09 17:56:42 by orudek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	free_data(t_data *data, int exit_status)
{
	(void)data;
	(void)exit_status;
	return (0);
}

int	create_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philo) * data->num_of_philos);
	if (!data->philos)
		return (0);
	data->threads = malloc(sizeof(pthread_t) * data->num_of_philos);
	if (!data->threads)
		return (free(data->philos), 0);
	i = -1;
	while (++i < data->num_of_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].state = 0;
		//data->philos[i].last_eat_time; ESTE SE PONE EN PHILO INIT
		data->philos[i].meals_remaining = data->num_of_meals;
		data->philos[i].time_to_eat = data->time_to_eat;
		data->philos[i].time_to_sleep = data->time_to_sleep;
		data->philos[i].forks[0] = data->forks[i];
		data->philos[i].forks[1] = data->forks[(i + 1) % data->num_of_philos];
		data->philos[i].write_lock = data->write_lock;
	}
	return (1);
}

void print_philo(t_philo *philo)
{
	printf("Philo data:\n");
	printf("\tid: %d\n",philo->id);
	printf("\tstate: %d\n",philo->state);
	printf("\tlast_eat_time: %d\n",philo->last_eat_time);
	printf("\tmeals_remaining: %d\n",philo->meals_remaining);
	printf("\ttime_to_eat: %d\n",philo->time_to_eat);
	printf("\ttime_to_sleep: %d\n",philo->time_to_sleep);
	printf("\tleft_fork: (%p)\n", &philo->forks[0]);
	printf("\tright_fork: (%p)\n", &philo->forks[1]);
	printf("\twrite_lock: (%p)\n", &philo->write_lock);
}

void	*philo_routine(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	pthread_mutex_lock(&philo->write_lock);
	print_philo(philo);
	pthread_mutex_unlock(&philo->write_lock);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		i;

	if (argc != 5 && argc != 6)
		return (1);
	if (!save_inputs(&data, argc, argv))
		return (1);
	if (!create_mutex(&data))
		return (1);
	if (!create_philos(&data))
		return (free_mutex(data.forks, data.num_of_philos), pthread_mutex_destroy(&data.write_lock));
	i = -1;
	while (++i < data.num_of_philos)
		pthread_create(&data.threads[i], NULL, philo_routine, &data.philos[i]);
	i = 0;
	while (i < data.num_of_philos)
		pthread_join(data.threads[i++],NULL);
	return (0);
}