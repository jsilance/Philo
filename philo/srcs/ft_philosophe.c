/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosophe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 14:23:03 by jusilanc          #+#    #+#             */
/*   Updated: 2023/05/20 13:49:09 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

unsigned long	ft_time_to_ms(struct timeval data)
{
	return ((data.tv_sec * 1000000 + data.tv_usec) / 1000);
}

void	ft_mut_print(int id, char *action, pthread_mutex_t *mut_print)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	pthread_mutex_lock(mut_print);
	printf("%ld %d %s\n", ft_time_to_ms(time), id, action);
	pthread_mutex_unlock(mut_print);
}

int	ft_is_dead(pthread_mutex_t *mut_dead, int *death)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(mut_dead);
	if (*death != 0)
		ret = 1;
	pthread_mutex_unlock(mut_dead);
	return (ret);
}

static int	ft_time_passed(struct timeval start, struct timeval end)
{
	return (ft_time_to_ms(end) - ft_time_to_ms(start));
}
// int ft_state_one()
// {}

void	*ft_philosophe(void *ptr)
{
	t_philo			*philo;
	struct timeval	last_eat;
	struct timeval	end;
	int				state;
	int				thinking;
	struct s_philo	*right_philo;
	int				thinking_ret;

	philo = (t_philo *)ptr;
	thinking = 1;
	state = 3;
	if (philo->id % 2)
		ft_sleep(philo->time_to_eat + philo->id * 2);
	if (philo->id + 1 > philo->nb_philo)
		right_philo = &philo->philos[0];
	else
		right_philo = &philo->philos[philo->id + 1];
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
			if (philo_eat(philo, &last_eat, &right_philo->left_fork,
					&right_philo->fork_available) == -1)
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
			// printf("id %d\n", right_philo->id);
			thinking_ret = philo_thinking(philo, &thinking,
					&right_philo->left_fork, &right_philo->fork_available);
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
	if (right_philo->fork_available == 0)
	{
		right_philo->fork_available = 1;
		pthread_mutex_unlock(&right_philo->left_fork);
	}
	return (NULL);
}
