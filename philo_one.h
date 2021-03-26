#ifndef PHILO_ONE_H
#define PHILO_ONE_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>


typedef struct s_env
{
	int nbT;
	int time_eat;
	int time_sleep;
	int time_die;
	long time_start;
	int *fork;
	pthread_mutex_t *else_death;
	pthread_t *pthread;
	int i;
	struct timeval time;
}t_env;

typedef struct s_philo
{
	int nb;
	int nbT;
	long old_time;
	int it;
	int has_eat;
	int has_sleep;
	long time_last_eat;
	int left;
	int right;
	int is_dead;
	int boucle;
	int *else_dead;
	t_env **info;
}	t_philo;

int error_return(char *str);
int parse_start(int ac, char **av, t_env *s);
int		ft_atoi(const char *nptr);
int		ft_isdigit(char *str);
void init_philo(t_philo *s, t_env *env, int i);
void start_loop(t_env *s);

#endif