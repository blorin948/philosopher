#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

int main()
{
	int i = 0;
	int c = fork();
	if (c == 0)
	{
		while (i++ < 10)
		{
			printf("salut\n");
			usleep(1);
		}
	}
	else
	{
		while (i++ < 10)
		{
			printf("acac\n");
			usleep(100000);
		}
	}
	wait(NULL);
}