#include "grocery.h"


int n_customers;
int n_chairs, available_chairs;
int customers_arrived = 0;
int customers_left = 0;
double total_wait = 0;

int main(int argc, char * argv[]){

    pthread_t grocer1, grocer2, customer;
    int i = 0, id1 = 0, id2 = 1, status = 0;
    time_t t;


    if (argc == 3) {
        n_customers = strtol(argv[1], NULL, 0);
        n_chairs = strtol(argv[2], NULL, 0);
        available_chairs = n_chairs;
        printf("Number of customers: %d \nNumber of chairs: %d\n", n_customers, n_chairs);
    }else{
        perror("Incorrect number of arguments.\n Usage: 'grocery n_customers(int) n_chairs(int)' \n");
        exit(EXIT_FAILURE);
    }

    printf("Grocery store opens!\n");

    /*Random generator initialization*/
    srand((unsigned) time(&t));

    /*Semaphore initialization*/
    sem_init(&grocers,0,0);
    sem_init(&customers,0,0);
    sem_init(&seat,0,1);

    /*Create grocer threads*/
    status = pthread_create(&grocer1, NULL, (void *)grocer_function, &id1);
    if(status != 0){
        perror("Error creating grocer thread.\n");
    }

    status = pthread_create(&grocer2, NULL, (void *)grocer_function, &id2);
    if(status != 0){
        perror("Error creating grocer thread.\n");
    }

    /*Create customer threads*/
    for(i = 0; i < n_customers; i++){

        /*Customers arrive one every 100ms*/
        usleep(100000);

        status = pthread_create(&customer, NULL, (void *)customer_function, (void *)&i);
        if(status != 0){
            perror("Error creating customer thread.\n");
        }
    }

    /*Wait all customers to finish ( pthread_join() )*/
    for(i = 0; i < n_customers; i++){
        pthread_join(customer, NULL);
    }

    printf("Customers that had to leave: %d \n", customers_left);

    /*Average waiting time for those that got serviced*/
    printf("Average waiting time: %f ms\n", (total_wait / (n_customers - customers_left)) );
    printf("Grocery store closes!\n");

    exit(EXIT_SUCCESS);
}

int *grocer_function(int *idp){

    int id = *idp;
    printf("Grocer #%d initialized!\n", id);
    while(1){
        /*Go to sleep*/
        sem_wait(&grocers);

        /*Critical region of serving a customer*/
        sem_wait(&seat);
        available_chairs++; //customer is being served, frees seat
        service_customer(id);
        sem_post(&seat);

        sem_post(&customers);
    }
}

void *customer_function(void *idp){

    /*Lock seat mutex*/
    sem_wait(&seat);
    customers_arrived++; //Another customer arrived
    printf("Customer %d just arrived!\n", customers_arrived);

    if(available_chairs > 0){
        available_chairs--;
        /*Release seat mutex*/
        sem_post(&seat);

        /*start waiting*/
        clock_t begin = clock();

        sem_post(&grocers); //wake one grocer
        sem_wait(&customers); //customer waits

        /*End of wait. Now the customer is being served.*/
        clock_t end = clock();
        double time_spent = (double) 1000000 * (end - begin) / CLOCKS_PER_SEC;
        /*Update the total waiting time for all customers*/
        total_wait+= time_spent;
    }else{
        /*Release seat mutex and customer leaves*/
        sem_post(&seat);
        customers_left++;
        printf("No seats available.Customer left.\n");
    }

    pthread_exit(0);
}


/*
  Simulates the time that passes until a customer
  is serviced by a grocer.
*/
void service_customer(int grocer_id){
    int service_time;

    service_time = rand() % 400000;
    usleep(service_time);

    printf("Grocer %d serviced customer for %d miliseconds\n", grocer_id, service_time / 1000);
}