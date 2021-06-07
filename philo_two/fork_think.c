#include "philo_two.h"

void	take_fork2(t_philo *s)
{
	sem_wait(s->info->fork);
	print_state(s, "has taken a fork");
	s->nb_fork++;
	sem_wait(s->info->fork);
	print_state(s, "has taken a fork");
	s->nb_fork++;
}

void	take_fork(t_philo *s)
{
	take_fork2(s);
	if (s->nb_fork == 2)
	{
		print_state(s, "is eating");
		s->has_sleep = 0;
		s->time_last_eat = ((1000000 * s->info->time.tv_sec \
		+ s->info->time.tv_usec) / 1000) - s->info->time_start;
		my_usleep(s->info->time_eat * 1000);
		s->info->nb_eat++;
		s->has_eat = 1;
		sem_post(s->info->fork);
		sem_post(s->info->fork);
		s->nb_fork = 0;
	}
}

void	think(t_philo *s)
{
	print_state(s, "is thinking");
	usleep(100);
}
