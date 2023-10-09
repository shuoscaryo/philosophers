/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orudek <orudek@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:41:42 by orudek            #+#    #+#             */
/*   Updated: 2023/10/09 17:56:23 by orudek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define MAX_INT 2147483647

typedef pthread_mutex_t	t_mtx;

typedef struct s_philo
{
	int		id;
	int		state; //0 waiting to eat, 1 sleeping
	int		last_eat_time;
	int		meals_remaining;
	int 	time_to_eat;
	int 	time_to_sleep;
	t_mtx	forks[2];
	t_mtx	write_lock;
}	t_philo;

typedef struct s_data
{
	int 		time_to_die;
	int 		time_to_eat;
	int 		time_to_sleep;
	int			num_of_meals;
	int			num_of_philos;
	t_mtx		write_lock;
	t_mtx 		*forks;
	pthread_t	*threads;
	t_philo		*philos;
}	t_data;

int	save_inputs(t_data *data, int argc, char **argv);
int	create_mutex(t_data *data);
int	free_mutex(pthread_mutex_t *mutex, int len);

#endif