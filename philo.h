/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nreher <nreher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 10:25:34 by nreher            #+#    #+#             */
/*   Updated: 2023/07/14 10:29:20 by nreher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# define FORK "has taken a fork\n"
# define FOOD "is eating\n"
# define SLEP "is sleeping\n"
# define THUNK "is thinking\n"
# define DED "died\n"

typedef struct s_person
{
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				social_security_number;
	int				time_of_foobs;
	struct s_data	*knowledge;
	long long		time_of_most_recent_meal;
}t_person;

typedef struct s_outside
{
	pthread_mutex_t	*forks;
}t_outside;

typedef struct s_data
{
	int				nop;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	int				dead;
	int				done_with_eating;
	long long		starting_time;
	pthread_mutex_t	voice;
	pthread_mutex_t	death;
}t_data;

void		populator(t_data *data, t_outside outside);
void		spawner(t_data *data, t_outside outside, t_person *population);
void		*brain(void *data);
int			string_to_int(char *data);
void		fork_factory(t_outside *outside, t_data *data);
void		think(t_person *person);
void		take_forks(t_person *person);
void		eat(t_person *person);
void		slep(t_person *person);
void		*reaper(void *perrson);
long long	gtod(void);
void		say(t_person *person, char *what);
int			checkded(t_person *person);
#endif
