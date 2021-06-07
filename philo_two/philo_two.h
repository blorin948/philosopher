#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>

typedef struct s_env
{
	int				nbT;
	int				time_eat;
	int				time_sleep;
	int				time_die;
	long			time_start;
	int				nbT_eat;
	int				nb_eat;
	int				error;
	sem_t			*fork;
	pthread_t		*pthread;
	sem_t			*print;
	struct timeval	time;
}				t_env;

typedef struct s_philo
{
	int				nb;
	long			old_time;
	int				it;
	int				has_eat;
	int				has_sleep;
	sem_t			*else_death;
	long			time_last_eat;
	int				left;
	int				right;
	int				nb_fork;
	int				is_dead;
	int				boucle;
	t_env			*info;
}				t_philo;

int		error_return(char *str);
void	init_env(t_env *s);
void	init_env2(t_env *s);
void	take_fork(t_philo *s);
int		parse_start(int ac, char **av, t_env *s);
int		ft_atoi(const char *nptr);
long	get_time(long old_time);
int		ft_isdigit(char *str);
void	init_philo(t_philo *s, t_env *env, int i);
void	start_loop(t_env *s, t_philo *philo);
void	my_usleep(int time);
void	print_state(t_philo *s, char *str);
void	think(t_philo *s);

#endif