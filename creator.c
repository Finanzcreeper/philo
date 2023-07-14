/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creator.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nreher <nreher@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 10:25:00 by nreher            #+#    #+#             */
/*   Updated: 2023/07/14 11:14:31 by nreher           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_data		data;
	t_outside	outside;

	if (argc != 5 && argc != 6)
	{
		printf("Not enough Args!\n");
		return (1);
	}
	data.nop = string_to_int(argv[1]);
	data.time_to_die = string_to_int(argv[2]);
	data.time_to_eat = string_to_int(argv[3]);
	data.time_to_sleep = string_to_int(argv[4]);
	data.number_of_times_each_philosopher_must_eat = string_to_int(argv[5]);
	data.done_with_eating = 0;
	data.dead = 0;
	if (data.nop == -1 || data.time_to_die == -1
		|| data.time_to_eat == -1 || data.time_to_sleep == -1
		|| data.number_of_times_each_philosopher_must_eat == -1)
	{
		printf("invalid data\n");
		return (1);
	}
	fork_factory(&outside, &data);
	free(outside.forks);
	return (0);
}

void	fork_factory(t_outside *outside, t_data *data)
{
	int	c;

	c = 0;
	outside->forks = malloc(data->nop
			* sizeof(pthread_mutex_t));
	while (c < data->nop)
		pthread_mutex_init(&outside->forks[c++], NULL);
	populator(data, *outside);
}

void	populator(t_data *data, t_outside outside)
{
	t_person	*population;
	int			c;

	c = 0;
	population = malloc (data->nop * sizeof(t_person));
	pthread_mutex_init(&data->voice, NULL);
	pthread_mutex_init(&data->death, NULL);
	while (c < data->nop)
	{
		population[c].right_fork = &outside.forks[c];
		if (c == 0)
			population[c].left_fork
				= &outside.forks[data->nop - 1];
		else
			population[c].left_fork = &outside.forks[c - 1];
		population[c].social_security_number = c + 1;
		population[c].knowledge = data;
		population[c].time_of_most_recent_meal = 0;
		population[c].time_of_foobs = 0;
		c++;
	}
	spawner(data, outside, population);
}

void	spawner(t_data *data, t_outside outside, t_person *population)
{
	pthread_t	*adressbook;
	int			c;

	adressbook = malloc(data->nop * sizeof(pthread_t *));
	c = 0;
	data->starting_time = gtod();
	while (c < data->nop)
	{
		pthread_create(&adressbook[c], NULL, brain, &population[c]);
		c++;
	}
	c = 0;
	while (1)
	{
		if (data->done_with_eating == data->nop)
			break ;
		if (data->dead == 1)
			break ;
	}
	c = 0;
	while (c < data->nop)
		pthread_join(adressbook[c++], NULL);
	free(adressbook);
	free(population);
}
