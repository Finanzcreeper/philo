/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nreher <nreher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 10:51:40 by nreher            #+#    #+#             */
/*   Updated: 2023/07/14 10:18:48 by nreher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	string_to_int(char *input)
{
	int	c;
	int	out;

	c = 0;
	out = 0;
	if (input == NULL)
		return (-2);
	while (input[c] != '\0')
	{
		if (input[c] < '0' || input[c] > '9')
			return (-1);
		out = out + (input[c++] - '0');
		out = out * 10;
	}
	out = out / 10;
	return (out);
}

long long	gtod(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	say(t_person *person, char *what)
{
	pthread_mutex_lock(&person->knowledge->voice);
	if (checkded(person) == 1)
	{
		pthread_mutex_unlock(&person->knowledge->voice);
		return ;
	}
	printf("%llu	%d %s", gtod() - person->knowledge->starting_time,
		person->social_security_number, what);
	pthread_mutex_unlock(&person->knowledge->voice);
}

int	checkded(t_person *person)
{
	if (person->knowledge->dead == 1)
		return (1);
	return (0);
}
