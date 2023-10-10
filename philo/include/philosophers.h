/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: orudek <orudek@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:41:42 by orudek            #+#    #+#             */
/*   Updated: 2023/10/10 20:27:51 by orudek           ###   ########.fr       */
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

typedef struct s_philo
{
	int		id;					//const
	int		state; 				//0 uninitialized, 1 active mutex
	t_ulong	start_time;			//mutex
	t_ulong	last_meal_time;		//mutex
	int		meals_remaining;	//no importa solo lo lee philo
	t_ulong	time_to_eat;		//const
	t_ulong	time_to_sleep;		//const
	t_mtx	*left_fork;			//const
	t_mtx	*right_fork;		//const
	t_mtx	*write_mtx;		//const
	t_mtx	philo_mtx;			//const
}	t_philo;

typedef struct s_data
{
	t_ulong		time_to_die;
	t_ulong		time_to_eat;
	t_ulong		time_to_sleep;
	int			num_of_meals;
	int			philos_num;
	t_mtx		write_mtx;
	t_mtx		*forks;
	pthread_t	*threads;
	t_philo		*philos;
	t_philo		*philo_dead;
	t_mtx		data_mtx;
}	t_data;

int		save_inputs(t_data *data, int argc, char **argv);
int		create_mutex(t_data *data);
int		free_mutex(pthread_mutex_t *mutex, int len);

void	sleep_ms(t_ulong ms);
t_ulong	get_time(void);

#endif