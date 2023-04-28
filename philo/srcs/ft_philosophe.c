/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosophe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 14:23:03 by jusilanc          #+#    #+#             */
/*   Updated: 2023/04/29 01:57:22 by jusilanc         ###   ########.fr       */
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
	// pthread_mutex_lock(&philo->mutex_fork);
	// pthread_mutex_lock(&right_fork);
	while (1)
	{
		if (state == 1)
		{
			gettimeofday(&end, NULL);
			printf("%ld %d is eating\n", ft_time_to_ms(end), philo->id);
			usleep(philo->time_to_eat * 1000);
			pthread_mutex_unlock(&philo->left_fork);
			pthread_mutex_unlock(&right_fork);
			state = 2;
			gettimeofday(&last_eat, NULL);
		}
		else if (state == 2)
		{
			gettimeofday(&end, NULL);
			printf("%ld %d is sleeping\n", ft_time_to_ms(end), philo->id);
			usleep(philo->time_to_sleep * 1000);
			state = 3;
		}
		else if (state == 3)
		{
			if (thinking == 0)
			{
				gettimeofday(&end, NULL);
				printf("%ld %d is thinking\n", ft_time_to_ms(end), philo->id);
				thinking = 1;
			}
			if (pthread_mutex_lock(&philo->left_fork) != 16
				&& pthread_mutex_lock(&right_fork) != 16)
			{
				gettimeofday(&end, NULL);
				printf("%ld %d has taken a fork\n", ft_time_to_ms(end),
						philo->id);
				state = 1;
				thinking = 0;
			}
		}
		gettimeofday(&end, NULL);
		if (ft_time_passed(last_eat, end) > philo->time_to_die)
		{
			printf("%ld %i died\n", ft_time_to_ms(end), philo->id);
			break ;
		}
	}
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(&right_fork);
	return (NULL);
}
