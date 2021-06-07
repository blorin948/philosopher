#include "philo_three.h"

void	init_env2(t_env *s)
{
	s->pthread = malloc(sizeof(pthread_t) * s->nbT);
}

void	init_philo(t_philo *s, t_env *env, int i)
{
	s->nb = i + 1;
	s->old_time = 0;
	s->has_eat = 0;
	s->has_sleep = 0;
	s->time_last_eat = 0;
	s->is_dead = 0;
	s->info = env;
}

void	init_env(t_env *s)
{
	s->nbT = 0;
	s->time_eat = 0;
	s->time_sleep = 0;
	s->time_die = 0;
	s->time_start = 0;
	s->nbT_eat = 0;
	s->nb_eat = 0;
	s->error = 0;
}
