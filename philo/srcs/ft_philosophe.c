/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosophe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 14:23:03 by jusilanc          #+#    #+#             */
/*   Updated: 2023/05/20 02:34:43 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

static unsigned long	ft_time_to_ms(struct timeval data)
{
	return ((data.tv_sec * 1000000 + data.tv_usec) / 1000);
}

static void	ft_mut_print(int id, char *action, pthread_mutex_t *mut_print)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	pthread_mutex_lock(mut_print);
	printf("%ld %d %s\n", ft_time_to_ms(time), id, action);
	pthread_mutex_unlock(mut_print);
}

static int	ft_is_dead(pthread_mutex_t *mut_dead, int *death)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(mut_dead);
	if (*death != 0)
		ret = 1;
	pthread_mutex_unlock(mut_dead);
	return (ret);
}

void	ft_sleep(int ms)
{
	struct timeval	start;
	struct timeval	current;

	gettimeofday(&start, NULL);
	gettimeofday(&current, NULL);
	while ((ft_time_to_ms(current) - ft_time_to_ms(start)) < (unsigned long)ms)
		gettimeofday(&current, NULL);
}

static int	ft_time_passed(struct timeval start, struct timeval end)
{
	return (ft_time_to_ms(end) - ft_time_to_ms(start));
}

static int	philo_eat(t_philo *philo, struct timeval *last_eat,
		pthread_mutex_t *right_fork, int *right_fork_available)
{
	if (ft_is_dead(philo->mut_dead, philo->death))
		return (-1);
	ft_mut_print(philo->id, "is eating", philo->printing);
	ft_sleep(philo->time_to_eat);
	*right_fork_available = 1;
	pthread_mutex_unlock(right_fork);
	philo->fork_available = 1;
	pthread_mutex_unlock(&philo->left_fork);
	gettimeofday(last_eat, NULL);
	return (0);
}

static int	philo_sleep(t_philo *philo)
{
	if (ft_is_dead(philo->mut_dead, philo->death))
		return (-1);
	ft_mut_print(philo->id, "is sleeping", philo->printing);
	ft_sleep(philo->time_to_sleep);
	return (0);
}

static int	philo_thinking(t_philo *philo, int *thinking,
		pthread_mutex_t *right_fork, int *right_fork_available)
{
	if (ft_is_dead(philo->mut_dead, philo->death))
		return (-1);
	if (*thinking == 0)
	{
		ft_mut_print(philo->id, "is thinking", philo->printing);
		*thinking = 1;
	}
	if (*right_fork_available == 1)
	{
		pthread_mutex_lock(right_fork);
		*right_fork_available = 0;
		if (philo->fork_available == 1)
		{
			ft_mut_print(philo->id, "has taken a fork", philo->printing);
			pthread_mutex_lock(&philo->left_fork);
			ft_mut_print(philo->id, "has taken a fork", philo->printing);
			*thinking = 0;
			philo->fork_available = 0;
		}
		else
		{
			pthread_mutex_unlock(right_fork);
			philo->fork_available = 1;
			return (1);
		}
	}
	return (0);
}

void	*ft_philosophe(void *ptr)
{
	t_philo			*philo;
	struct timeval	last_eat;
	struct timeval	end;
	int				state;
	int				thinking;
	struct s_philo	right_philo;
	int				thinking_ret;

	philo = (t_philo *)ptr;
	thinking = 1;
	state = 3;
	if (philo->id % 2)
		ft_sleep(philo->time_to_eat + philo->id * 2);
	if (philo->id + 1 > philo->nb_philo)
		right_philo = philo->philos[0];
	else
		right_philo = philo->philos[philo->id + 1];
	gettimeofday(&last_eat, NULL);
	while (1)
	{
		if (ft_is_dead(philo->mut_dead, philo->death))
			break ;
		if (state == 1)
		{
			if (philo->nb_to_eat > 0)
				philo->nb_to_eat--;
			else if (philo->nb_to_eat == 0)
				break ;
			if (philo_eat(philo, &last_eat, &right_philo.left_fork,
					&right_philo.fork_available) == -1)
				break ;
			state = 2;
		}
		else if (state == 2)
		{
			if (philo_sleep(philo) == -1)
				break ;
			state = 3;
		}
		else if (state == 3)
		{
			if (ft_is_dead(philo->mut_dead, philo->death))
				break ;
			thinking_ret = philo_thinking(philo, &thinking,
					&right_philo.left_fork, &right_philo.fork_available);
			if (thinking_ret == -1)
				break ;
			else if (!thinking_ret)
				state = 1;
		}
		gettimeofday(&end, NULL);
		if (ft_time_passed(last_eat, end) > philo->time_to_die)
		{
			if (ft_is_dead(philo->mut_dead, philo->death))
				break ;
			ft_mut_print(philo->id, "died", philo->printing);
			*philo->death = 1;
			break ;
		}
	}
	if (philo->fork_available == 0)
	{
		philo->fork_available = 1;
		pthread_mutex_unlock(&philo->left_fork);
	}
	if (right_philo.fork_available == 0)
	{
		right_philo.fork_available = 1;
		pthread_mutex_unlock(&right_philo.left_fork);
	}
	return (NULL);
}
