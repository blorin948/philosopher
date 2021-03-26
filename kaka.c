#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>


int main(int ac, char **av)
{
    struct timeval current_time;
    struct timeval current_time2;

    gettimeofday(&current_time, NULL);
    int i = 0;
    while (i < 100)
    {
        gettimeofday(&current_time2, NULL);
        printf("micro_seconds :     %d\n", current_time2.tv_usec - current_time.tv_usec);
        //printf("seconds : %ld     micro_seconds :     %ld\n",current_time2.tv_sec - current_time.tv_sec, (long int)(current_time2.tv_usec - current_time.tv_usec));
        usleep(1000);
        i++;
    }
}