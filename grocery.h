#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

sem_t grocers;
sem_t customers;
sem_t seat;

int 	*grocer_function(int *idp);
void *customer_function(void *idp);
void service_customer(int grocer_id);