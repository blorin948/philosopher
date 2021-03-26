#include "philo_one.h"

void init_philo(t_philo *s, t_env *env, int i)
{
	s->nb = i + 1;
	s->old_time = 0;
	s->has_eat = 0;
	s->has_sleep = 0;
	s->time_last_eat = 0;
	int left;
	int right;
	s->is_dead = 0;
	s->info = &env;
}


void init_fork(t_env *s)
{
	int i = 0;
	s->fork = malloc(sizeof(int) * s->nbT);
    while (i < s->nbT)
	{
		s->fork[i] = 1;
		i++;
	}
}

void init_philo2(t_env *s)
{
	s->pthread = malloc(sizeof(pthread_t) *  s->nbT);
	init_fork(s);
}
