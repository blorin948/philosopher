#include "philo_one.h"

void	take_fork2(t_philo *s, int left, int right)
{
	if (s->nb == s->info->nbT)
	{
		pthread_mutex_lock(&s->info->fork_m[right]);
		print_state(s, "has taken a fork");
		s->info->fork[right] = 0;
		s->right = 1;
		pthread_mutex_lock(&s->info->fork_m[left]);
		print_state(s, "has taken a fork");
		s->info->fork[left] = 0;
		s->left = 1;
	}
	else
	{
		pthread_mutex_lock(&s->info->fork_m[left]);
		print_state(s, "has taken a fork");
		s->info->fork[left] = 0;
		s->left = 1;
		pthread_mutex_lock(&s->info->fork_m[right]);
		print_state(s, "has taken a fork");
		s->info->fork[right] = 0;
		s->right = 1;
	}
}

void	take_fork(t_philo *s)
{
	int	left;
	int	right;

	left = s->nb - 1;
	right = s->nb - 2;
	if (s->nb == 1)
		right = s->info->nbT - 1;
	take_fork2(s, left, right);
	if (s->right == 1 && s->left == 1)
	{
		print_state(s, "is eating");
		s->has_sleep = 0;
		s->time_last_eat = ((1000000 * s->info->time.tv_sec \
		+ s->info->time.tv_usec) / 1000) - s->info->time_start;
		my_usleep(s->info->time_eat * 1000);
		s->info->nb_eat++;
		s->info->fork[left] = 1;
		s->info->fork[right] = 1;
		s->has_eat = 1;
		s->left = 0;
		s->right = 0;
		pthread_mutex_unlock(&s->info->fork_m[left]);
		pthread_mutex_unlock(&s->info->fork_m[right]);
	}
}

void	think(t_philo *s)
{
	print_state(s, "is thinking");
	usleep(100);
}
