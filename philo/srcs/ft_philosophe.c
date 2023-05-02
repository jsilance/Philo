/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosophe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 14:23:03 by jusilanc          #+#    #+#             */
/*   Updated: 2023/05/03 00:45:49 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

static unsigned long	ft_time_to_ms(struct timeval data)
{
	return ((data.tv_sec * 1000000 + data.tv_usec) / 1000);
}

static int	ft_time_passed(struct timeval start, struct timeval end)
{
	return (ft_time_to_ms(end) - ft_time_to_ms(start));
}

static int	philo_eat(t_philo *philo, struct timeval *last_eat,
		struct timeval *end, pthread_mutex_t *right_fork)
{
	if (*philo->death == 1)
		return (-1);
	gettimeofday(end, NULL);
	pthread_mutex_lock(philo->printing);
	printf("%ld %d is eating\n", ft_time_to_ms(*end), philo->id);
	pthread_mutex_unlock(philo->printing);
	usleep(philo->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(right_fork);
	gettimeofday(last_eat, NULL);
	return (0);
}

static int	philo_sleep(t_philo *philo, struct timeval *end)
{
	if (*philo->death == 1)
		return (-1);
	gettimeofday(end, NULL);
	pthread_mutex_lock(philo->printing);
	printf("%ld %d is sleeping\n", ft_time_to_ms(*end), philo->id);
	pthread_mutex_unlock(philo->printing);
	usleep(philo->time_to_sleep * 1000);
	return (0);
}

static int	philo_thinking(t_philo *philo, struct timeval *end, int *thinking,
		pthread_mutex_t *right_fork)
{
	if (*thinking == 0)
	{
		if (*philo->death == 1)
			return (-1);
		gettimeofday(end, NULL);
		pthread_mutex_lock(philo->printing);
		printf("%ld %d is thinking\n", ft_time_to_ms(*end), philo->id);
		pthread_mutex_unlock(philo->printing);
		*thinking = 1;
	}
	if (*philo->death == 1)
		return (-1);
	pthread_mutex_lock(&philo->left_fork);
	pthread_mutex_lock(philo->printing);
	printf("%ld %d has taken a fork\n", ft_time_to_ms(*end), philo->id);
	pthread_mutex_unlock(philo->printing);
	if (*philo->death == 1)
		return (-1);
	pthread_mutex_lock(right_fork);
	pthread_mutex_lock(philo->printing);
	printf("%ld %d has taken a fork\n", ft_time_to_ms(*end), philo->id);
	pthread_mutex_unlock(philo->printing);
	gettimeofday(end, NULL);
	*thinking = 0;
	return (0);
}

void	*ft_philosophe(void *ptr)
{
	t_philo			*philo;
	struct timeval	last_eat;
	struct timeval	end;
	int				state;
	int				thinking;
	pthread_mutex_t	right_fork;

	philo = (t_philo *)ptr;
	thinking = 0;
	state = 3;
	if (philo->id + 1 > philo->nb_philo)
		right_fork = philo->philos[0].left_fork;
	else
		right_fork = philo->philos[philo->id + 1].left_fork;
	gettimeofday(&last_eat, NULL);
	while (1)
	{
		if (*philo->death == 1)
			break ;
		if (state == 1)
		{
			if (philo_eat(philo, &last_eat, &end, &right_fork) == -1)
				break ;
			state = 2;
		}
		else if (state == 2)
		{
			if (philo_sleep(philo, &end) == -1)
				break ;
			state = 3;
		}
		else if (state == 3)
		{
			if (philo_thinking(philo, &end, &thinking, &right_fork) == -1)
				break ;
			state = 1;
		}
		gettimeofday(&end, NULL);
		if (ft_time_passed(last_eat, end) > philo->time_to_die)
		{
			if (*philo->death == 1)
				break ;
			pthread_mutex_lock(philo->printing);
			printf("%ld %i died\n", ft_time_to_ms(end), philo->id);
			pthread_mutex_unlock(philo->printing);
			*philo->death = 1;
			break ;
		}
	}
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(&right_fork);
	return (NULL);
}
