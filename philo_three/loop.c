#include "philo_three.h"

int	is_dead(t_philo *s)
{
	long	last_eat;
	long	current_mili;

	gettimeofday(&s->info->time, NULL);
	last_eat = s->time_last_eat;
	current_mili = ((1000000 * s->info->time.tv_sec \
	+ s->info->time.tv_usec) / 1000) - s->info->time_start;
	if (last_eat + s->info->time_die <= current_mili)
	{
		sem_wait(s->info->print);
		sem_post(s->else_death);
		printf("%ld		Philo number %d is dead\n", ((1000000 \
		* s->info->time.tv_sec + s->info->time.tv_usec) / 1000) \
		- s->info->time_start, s->nb);
		exit(EXIT_SUCCESS);
	}
	if (s->info->nbT_eat > 0 && s->info->nb_eat >= s->info->nbT_eat)
	{
		my_usleep(s->info->time_eat * s->info->time_sleep);
		sem_wait(s->info->print);
		printf("all philo eat %d times\n", s->info->nbT_eat);
		sem_post(s->else_death);
		exit(EXIT_SUCCESS);
	}
	return (1);
}

void	*death_loop(void *arg)
{
	t_philo	*s;

	s = (struct s_philo *)arg;
	while (is_dead(s))
		usleep(100);
	return ((void *) 0);
}

void	p_sleep(t_philo *s)
{
	print_state(s, "is sleeping");
	my_usleep(s->info->time_sleep * 1000);
	s->has_eat = 0;
	s->has_sleep = 1;
}

void	*loop(t_philo *s)
{
	pthread_t	death_thread;

	if (s->nb % 2 != 0)
		usleep(500);
	if (pthread_create(&death_thread, NULL, death_loop, s) != 0)
		exit(EXIT_SUCCESS);
	while (1)
	{
		if (s->has_eat == 0)
			take_fork(s);
		if (s->has_sleep == 0)
			p_sleep(s);
		think(s);
	}
}
