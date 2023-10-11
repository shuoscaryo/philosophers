/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orudek <orudek@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:41:42 by orudek            #+#    #+#             */
/*   Updated: 2023/10/11 16:13:17 by orudek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>

# define MAX_INT 2147483647
# define SLEEP_TICKS 100

typedef pthread_mutex_t	t_mtx;
typedef unsigned long	t_ulong;

enum
{
	TAKE_FORK_MSG,
	EATING_MSG,
	SLEEPING_MSG,
	THINKING_MSG,
	DEAD_MSG
};

typedef struct s_shared
{
	t_ulong		start_time;
	t_ulong		eat_time;
	t_ulong		sleep_time;
	t_ulong		death_time;
	int			meals_num;
	int			philos_num;
	int			end;
	t_mtx		write_mtx;
}	t_shared;

typedef struct s_philo
{
	int			id;
	t_ulong		last_meal_time;
	int			meals_remaining;
	t_mtx		*left_fork;
	t_mtx		*right_fork;
	t_mtx		philo_mtx;
	t_shared	*shared;
}	t_philo;

typedef struct s_data
{
	t_mtx		*forks;
	pthread_t	*threads;
	t_philo		*philos;
	t_shared	shared;
}	t_data;

int		init_data(t_data *data, int argc, char **argv);
int		init_shared(t_shared *shared, int argc, char **argv);
int		init_forks(t_data *data);
int		init_philos(t_data *data);
void	free_mutex(pthread_mutex_t *mutex, int len);
void	*philo_routine(void *data);

void	sleep_ms(t_ulong ms);
t_ulong	get_time(void);

#endif