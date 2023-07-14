/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grim_reaper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nreher <nreher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 12:29:58 by nreher            #+#    #+#             */
/*   Updated: 2023/07/14 11:10:40 by nreher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*reaper(void *perrson)
{
	t_person	*person;
	int			done;

	done = 0;
	person = (t_person *) perrson;
	while (person->knowledge->dead == 0)
	{
		if (done == 0 && person->time_of_foobs
			== person->knowledge->number_of_times_each_philosopher_must_eat)
			person->knowledge->done_with_eating += ++done;
		if (gtod() - person->knowledge->starting_time
			> person->time_of_most_recent_meal + person->knowledge->time_to_die)
		{
			if (checkded(person) == 1)
				break ;
			say(person, DED);
			person->knowledge->dead = 1;
			if (person->left_fork == person->right_fork)
				pthread_mutex_unlock(person->left_fork);
			break ;
		}
		if (person->knowledge->done_with_eating == person->knowledge->nop)
			break ;
	}
	return (NULL);
}
