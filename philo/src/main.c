/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orudek <orudek@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:37:58 by orudek            #+#    #+#             */
/*   Updated: 2023/10/13 17:29:52 by orudek           ###   ########.fr       */
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
