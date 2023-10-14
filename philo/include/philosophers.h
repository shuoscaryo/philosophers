/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orudek <orudek@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:41:42 by orudek            #+#    #+#             */
/*   Updated: 2023/10/14 16:00:34 by orudek           ###   ########.fr       */
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

# define TAKE_FORK_MSG "has taken a fork"
# define EATING_MSG "is eating"
# define SLEEPING_MSG "is sleeping"
# define THINKING_MSG "is thinking"
# define DEAD_MSG "died"

typedef struct s_shared
{
	t_ulong		start_time;
	t_ulong		eat_time;
	t_ulong		sleep_time;
	t_ulong		death_time;
	int			meals_num;
	int			philos_num;
	char		end;
	t_mtx		shared_mtx;
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
void	*philo_routine(void *data);
void	philo_speak(t_philo *philo, char *msg);
int		check_end(t_data *data);
void	sleep_ms(t_ulong ms);
t_ulong	get_time(void);

#endif