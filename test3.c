#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>


struct timeval current_time;
  
typedef struct s_philo
{
    int nb;
    int **fourch;
	int nbT;
	int it;
	int has_eat;
	int has_sleep;
	int time_eat;
	int time_sleep;
	int time_die;
	long time_last_eat;
	int left;
	int right;
	int boucle;
	int *else_dead;
	pthread_mutex_t **death;
	pthread_mutex_t **mutex;
}               t_philo;


void use_sleep(long time)
{
	int i = 0;
	long tmp = time/100;
	while (i < 100)
	{
		usleep(tmp);
		i++;
	}
}

void print_state(t_philo *s, char *str)
{
	int i = 0;
	gettimeofday(&current_time, NULL);
	printf("%ld Philo number %d is %s\n", (1000000 * current_time.tv_sec + current_time.tv_usec) / 1000, s->nb, str);
}

int is_dead(t_philo *s)
{
	long last_eat = s->time_last_eat;
	long current_mili = (1000000 * current_time.tv_sec + current_time.tv_usec) / 1000;
	gettimeofday(&current_time, NULL);
	//printf("last eat = %ld    die time = %ld\n", last_eat + s->time_die, current_mili);
	if (last_eat + s->time_die < current_mili || *s->else_dead == 1)
	{
		if (*s->else_dead == 0)
		{
			pthread_mutex_lock(*s->death);
			*s->else_dead = 1;
			pthread_mutex_unlock(*s->death);
		}
		print_state(s, "dead");
		return (0);
	}
	return (1);
}

void nb_fork(t_philo *s)
{
	int i = 0;
	while (s->fourch[0][i])
	{
		i++;
	}
	printf("%d fourchettes dispo \n", i + 2);
}

void take_fork(t_philo *s)
{
	int left = s->nb;
	int right = s->nb - 1;
	if (s->nb == s->nbT)
		left = 0;
		if (s->nb == s->nbT)
		{
			if (s->fourch[0][right] == 1)
			{
				pthread_mutex_lock(&s->mutex[0][right]);
				s->fourch[0][right] = 0;
				s->right = 1;
			}
			if (s->fourch[0][left] == 1)
			{
				pthread_mutex_lock(&s->mutex[0][left]);
				s->fourch[0][left] = 0;
				s->left = 1;
			}
			}
		}
	else
	{
		if (s->fourch[0][left] == 1)
		{
			pthread_mutex_lock(&s->mutex[0][left]);
			s->fourch[0][left] = 0;
			s->left = 1;
		}
		if (s->fourch[0][right] == 1)
		{
			pthread_mutex_lock(&s->mutex[0][right]);
			s->fourch[0][right] = 0;
			s->right = 1;
		}
	}
	if (s->right == 1 && s->left == 1)
	{
		print_state(s, "eating");
		s->has_sleep = 0;
		s->time_last_eat = (1000000 * current_time.tv_sec + current_time.tv_usec) / 1000;
		use_sleep(s->time_eat * 1000);
		s->fourch[0][left] = 1;
		s->fourch[0][right] = 1;
		s->has_eat = 1;
		s->left = 0;
		s->right = 0;
		pthread_mutex_unlock(&s->mutex[0][left]);
		pthread_mutex_unlock(&s->mutex[0][right]);
	}
	//if ((s->right == 1 && s->left == 0) || (s->right == 0 && s->left == 1))
	//	exit(0);
}


void p_sleep(t_philo *s)
{
	print_state(s, "sleeping");
	use_sleep(s->time_sleep * 1000);
	s->has_sleep = 1;
	s->has_eat = 0;
}

pthread_mutex_t *create_mutex_tab(t_philo *s, int nb_philo)
{
	int i = 0;
	pthread_mutex_t *mutex;
	mutex = malloc(sizeof(pthread_mutex_t) * nb_philo);
	while (i < nb_philo)
	{
		pthread_mutex_init(&mutex[i], NULL);
		i++;
	}
	return (mutex);
}

int *create_fork_tab(t_philo *s, int nb_philo)
{
	int *fork;
	int i = 0;
	if (!(fork = malloc(sizeof(int) * nb_philo)))
        return 0;
    while (i < nb_philo)
	{
		fork[i] = 1;
		i++;
	}
	return (fork);
}

void think(t_philo *s)
{
	printf("%d Philo number %d is thinking\n", current_time.tv_usec, s->nb);
	usleep(1000);
}

void *death_loop(void *ok)
{
	t_philo *s = (struct s_philo *)ok;
	while (is_dead(s))
	{
		
	}
	printf("LAALALLALALALALALALALALALALALALALALALALALALALALALALALALALALALALALALALALALALALALALALALALALALALALALALALALALA222222222\n");
	return ((void*)1);
}

void *salut(void *ok)
{
	t_philo *s = (struct s_philo *)ok;
	int x = 0;
	s->boucle = 0;
	pthread_t death_thread;
	if (pthread_create(&death_thread, NULL, death_loop, ok) != 0)
	{
		printf("LAALALLALALALALALALALALALALALALALALALALALALALALALALALALALALALALALALALALALALALALALALALALALALALALALALALALALA\n");
		return ((void*)1);
	}
	pthread_detach(death_thread);
//	void *val;
//		pthread_join(death_thread, val);
//	int xa = (int)val;
	while (1)
	{
	//	printf("%d\n", *s->else_dead);
		if (s->nb % 2 == 0 && x == 0)
			usleep(1000);
		if (s->has_eat == 0)
			take_fork(s);
		if (s->has_sleep == 0 && s->has_eat == 1)
			p_sleep(s);
		x++;
	}
	//printf("PHILO = %d   time EAT = %d TIME DIE =%d TIME SLEEP %d HAS SLEEP %d HAS EAT  %d\n", s->nb, s->time_eat, s->time_die, s->time_sleep, s->has_sleep, s->has_eat);
    return (void*)0;
}

void init_s(t_philo *s)
{
	gettimeofday(&current_time, NULL);
	s->time_eat = 200;
	s->time_die = 300;
	s->time_sleep = 200;
	s->has_sleep = 0;
	s->has_eat = 0;
	s->time_last_eat = (1000000 * current_time.tv_sec + current_time.tv_usec) / 1000;
}

int main(int ac, char **av)
{
	   int i = 0;
    t_philo *s;
   int nb_philo = 4;
   pthread_t *philo;
if (!(s = malloc(sizeof(t_philo ) * nb_philo)))
        return (0);
if (!(philo = malloc(sizeof(pthread_t) * nb_philo)))	
    return 0;
	init_s(s+i);
		int *fork;
		pthread_mutex_t *mutex;
	mutex = create_mutex_tab(s, nb_philo);
	while (i < nb_philo)
    {
        (s+i)->mutex = &mutex;
        i++;
    }
	pthread_mutex_t *death1;
	death1 = malloc(sizeof(pthread_mutex_t) * 1);
	pthread_mutex_init(death1, NULL);
	i = 0;
	int *els = malloc(sizeof(int) * 1);
	while (i < nb_philo)
	{
		(s+i)->else_dead = *&els;
		i++;
	}
	els = 0;
	i = 0;
	while (i < nb_philo)
	{
		(s+i)->death = &death1;
		i++;
	}
    fork = create_fork_tab(s, nb_philo);
	i = 0;
	while (i < nb_philo)
    {
        (s+i)->fourch = &fork;
        i++;
    }
	int nb = 1;
	i = 0;
	while (i < nb_philo)
	{
		(s+i)->nb = nb;
		(s+i)->nbT = nb_philo;
		init_s(s+i);
		if (pthread_create(&philo[i], NULL, salut, (void*)(s+i)) != 0)
			exit(0);
		i++;
		nb++;
	}
	i = 0;
	while (i < nb_philo)
	{
		pthread_join(philo[i], NULL);
		i++;
	}
    //usleep(100000);
}