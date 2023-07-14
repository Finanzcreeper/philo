/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thinkies_guy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nreher <nreher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 11:11:37 by nreher            #+#    #+#             */
/*   Updated: 2023/07/14 11:14:50 by nreher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*brain(void *perrson)
{
	pthread_t	grim_reaper;
	t_person	*person;

	person = (t_person *)perrson;
	pthread_create(&grim_reaper, NULL, reaper, person);
	pthread_detach(grim_reaper);
	while (person->knowledge->dead == 0)
	{
		think(person);
		take_forks(person);
		eat(person);
		if (person->knowledge->number_of_times_each_philosopher_must_eat
			!= -2 && person->time_of_foobs
			< person->knowledge->number_of_times_each_philosopher_must_eat)
			person->time_of_foobs++;
		if (person->knowledge->done_with_eating
			== person->knowledge->nop)
			break ;
		slep(person);
		if (checkded(person) == 1)
			break ;
	}
	return (NULL);
}

void	think(t_person *person)
{
	say(person, THUNK);
}

void	take_forks(t_person *person)
{
	if (person->social_security_number % 2 == 1)
	{
		pthread_mutex_lock(person->left_fork);
		say(person, FORK);
		pthread_mutex_lock(person->right_fork);
		say(person, FORK);
	}
	else
	{
		pthread_mutex_lock(person->right_fork);
		say(person, FORK);
		pthread_mutex_lock(person->left_fork);
		say(person, FORK);
	}
}

void	eat(t_person *person)
{
	person->time_of_most_recent_meal = gtod()
		- person->knowledge->starting_time;
	say(person, FOOD);
	usleep(person->knowledge->time_to_eat * 1000);
	pthread_mutex_unlock(person->left_fork);
	pthread_mutex_unlock(person->right_fork);
}

void	slep(t_person *person)
{
	say(person, SLEP);
	usleep(person->knowledge->time_to_sleep * 1000);
}
