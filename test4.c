#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>


struct timeval current_time;
typedef struct s_time
{
	long mili;
}	t_time;


typedef struct s_big
{
	int nbT;
	int time_eat;
	int time_sleep;
	int time_die;
	pthread_mutex_t print;
	t_philo *s;
}t_big;

typedef struct s_philo
{
    int nb;
    int **fourch;
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
	pthread_mutex_t *else_death;
	pthread_mutex_t **death;
	pthread_mutex_t **mutex;
	t_time time;
}               t_philo;


/*void get_time(t_philo *s)
{
	gettimeofday(&current_time, NULL);
	s->time->mili = (1000000 * current_time.tv_sec + current_time.tv_usec) / 1000;
}*/

void print_state(t_philo *s, char *str)
{
	int i = 0;
	gettimeofday(&current_time, NULL);
	printf("%ld Philo number %d is %s\n", ((1000000 * current_time.tv_sec + current_time.tv_usec) / 1000) - s->old_time, s->nb, str);
}

void	my_usleep(int time)
{
	struct timeval	t;
	struct timeval	act;
	long mili;
	long curr_mili;
	gettimeofday(&t, NULL);
//	t.tv_sec += (t.tv_usec + time) / 1000000;
//	t.tv_usec = (t.tv_usec + time) % 1000000;
	mili = (1000000 * t.tv_sec + t.tv_usec + time) / 1000;
	gettimeofday(&act, NULL);
	curr_mili = (1000000 * act.tv_sec + act.tv_usec) / 1000;
	while (curr_mili < mili)
	{
		usleep(50);
		gettimeofday(&act, NULL);
		curr_mili = (1000000 * act.tv_sec + act.tv_usec) / 1000;
	}
}

void test(t_philo *s)
{
	int i = 0;
	printf("philo n %d    else dead = %d\n", s->nb, *s->else_dead);
}


int is_dead(t_philo *s)
{
	long last_eat = s->time_last_eat;
	long current_mili = (1000000 * current_time.tv_sec + current_time.tv_usec) / 1000;
	gettimeofday(&current_time, NULL);
	//printf("last eat = %ld    die time = %ld\n", last_eat + s->time_die, current_mili);
	if (last_eat + s->time_die < current_mili || *s->else_dead == 1)
	{
		pthread_mutex_lock(*s->death);
		if (*s->else_dead == 0)
		{
			pthread_mutex_unlock(s->else_death);
			*s->else_dead = 1;
			s->is_dead = 1;
		}
		pthread_mutex_unlock(*s->death);
		//print_state(s, "dead");
		//exit(0);
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
		pthread_mutex_lock(&s->mutex[0][right]);
		print_state(s, "taken a fork");
		s->fourch[0][right] = 0;
		s->right = 1;
		pthread_mutex_lock(&s->mutex[0][left]);
		print_state(s, "taken a fork");
		s->fourch[0][left] = 0;
		s->left = 1;	
	}
	else
	{
		pthread_mutex_lock(&s->mutex[0][left]);
		print_state(s, "taken a fork");
		s->fourch[0][left] = 0;
		s->left = 1;
		pthread_mutex_lock(&s->mutex[0][right]);
		print_state(s, "taken a fork");
		s->fourch[0][right] = 0;
		s->right = 1;
	}
	if (s->right == 1 && s->left == 1)
	{
		print_state(s, "eating");
		s->has_sleep = 0;
		s->time_last_eat = (1000000 * current_time.tv_sec + current_time.tv_usec) / 1000;
		my_usleep(s->time_eat * 1000);
		s->fourch[0][left] = 1;
		s->fourch[0][right] = 1;
		s->has_eat = 1;
		s->left = 0;
		s->right = 0;
		pthread_mutex_unlock(&s->mutex[0][left]);
		pthread_mutex_unlock(&s->mutex[0][right]);
	}
}


void p_sleep(t_philo *s)
{
	print_state(s, "sleeping");
	my_usleep(s->time_sleep * 1000);
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
	usleep(100);
}

void *death_loop(void *ok)
{
	t_philo *s = (struct s_philo *)ok;
	while (is_dead(s))
	{
		usleep(500);
	}
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
		printf("XAXXAXXXAXAAXXAXAXAXAXAXAXAXXAX\n");
		return ((void*)1);
	}
	while (1)
	{
		if (*s->else_dead == 1)
		{
			return ((void*)1);
		}
		if (s->nb % 2 == 0)
			usleep(500);
		if (s->has_eat == 0)
			take_fork(s);
		if (s->has_sleep == 0 && s->has_eat == 1)
			p_sleep(s);
		x++;
	}
    return (void*)0;
}

void init_s(t_philo *s, long time)
{
	gettimeofday(&current_time, NULL);
	s->has_sleep = 0;
	s->has_eat = 0;
	s->old_time = time;
	s->is_dead = 0;
	s->time_last_eat = (1000000 * current_time.tv_sec + current_time.tv_usec) / 1000;
}

void init_big(t_big *s)
{
	s->time_eat = 200;
	s->time_die = 800;
	s->time_sleep = 200;
}

int main(int ac, char **av)
{
	t_big *big;
	if (!(big = malloc(sizeof(t_big))))
		return (0);
	init_big(big);
	   int i = 0;
    t_philo *s;
   int nb_philo = 150;
   pthread_t *philo;
if (!(big->s = malloc(sizeof(t_philo ) * nb_philo)))
        return (0);
if (!(philo = malloc(sizeof(pthread_t) * nb_philo)))	
    return 0;
	gettimeofday(&current_time, NULL);
	long time = (1000000 * current_time.tv_sec + current_time.tv_usec) / 1000;
	init_s(s+i, time);
		int *fork;
		pthread_mutex_t *mutex;
			pthread_mutex_t utex;
	pthread_mutex_init(&utex, NULL);
	pthread_mutex_lock(&utex);
	i = 0;
	while (i < nb_philo)
	{
		(s+i)->else_death = &utex;
		i++;
	}
	i = 0;
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
		init_s(s+i, time);
		pthread_create(&philo[i], NULL, salut, (void*)(s+i));
		pthread_detach(philo[i]);
		i++;
		nb++;
	}
	i = 0;
	t_philo *retur;
	i = 0;
	pthread_mutex_lock(&utex);
	pthread_mutex_unlock(&utex);
	while (i < nb_philo)
	{
		if ((s+i)->is_dead == 1)
			print_state((s+i), "dead");
		i++;
	}
}