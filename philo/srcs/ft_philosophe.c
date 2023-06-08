/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philosophe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jusilanc <jusilanc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 14:23:03 by jusilanc          #+#    #+#             */
/*   Updated: 2023/06/08 11:04:08 by jusilanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_philo.h"

unsigned long	ft_time_to_ms(struct timeval data)
{
	return ((data.tv_sec * 1000000 + data.tv_usec) / 1000);
}

int	ft_mut_print(int id, char *action, pthread_mutex_t *mut_print)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	if (pthread_mutex_lock(mut_print) == -1)
		return (-1);
	printf("%ld %d %s\n", ft_time_to_ms(time), id, action);
	if (pthread_mutex_unlock(mut_print) == -1)
		return (-1);
	return (0);
}

int	ft_time_passed(struct timeval start, struct timeval end)
{
	return (ft_time_to_ms(end) - ft_time_to_ms(start));
}

static void	philo_state_init(t_philo_state *p)
{
	p->thinking = 1;
	p->state = THINKING;
	if (p->philo->id % 2)
		ft_sleep(p->philo->time_to_eat + p->philo->id * 2);
	if (p->philo->id + 1 > p->philo->nb_philo)
		p->right_philo = &p->philo->philos[0];
	else
		p->right_philo = &p->philo->philos[p->philo->id];
	gettimeofday(&p->last_eat, NULL);
}

void	*ft_philosophe(void *ptr)
{
	t_philo_state	p;

	p.philo = (t_philo *)ptr;
	philo_state_init(&p);
	while (1)
	{
		if (ft_is_dead(p.philo->mut_dead, p.philo->death))
			break ;
		if (p.state == EAT && eating_part(p.philo, &p.last_eat, p.right_philo,
				&p.state))
			break ;
		else if (p.state == SLEEP && philo_sleep(p.philo, &p.state))
			break ;
		else if (p.state == THINKING && thinking_part(&p))
			break ;
		if (death_part(&p))
			break ;
	}
	ft_philo_releaser(&p.philo->left_fork, &p.philo->fork_available,
		&p.philo->total_fork);
	ft_philo_releaser(&p.right_philo->left_fork, &p.right_philo->fork_available,
		&p.right_philo->total_fork);
	return (NULL);
}
