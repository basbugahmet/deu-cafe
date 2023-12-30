#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>
#include <time.h>

#define CUSTOMER_NUMBER 25
#define CUSTOMER_ARRIVAL_TIME_MIN 1
#define CUSTOMER_ARRIVAL_TIME_MAX 3
#define REGISTER_NUMBER 5
#define COFFEE_TIME_MIN 2
#define COFFEE_TIME_MAX 5


sem_t semaphore; // defining the semaphore


int registers[REGISTER_NUMBER]; // Defining a register array whose length is of the defined register number.



void* cafe(void* args) {
    sem_wait(&semaphore); // the function here decrements the value of the semaphore that is greater than zero
    srand(time(NULL)); // this function is used to generate a random number, and in order to make it randomized each time the program is run, we have to pass the NULL parameter for the time.
    int customerID = *(int*) args; // defining a pointer that is assigned for a thread
    int registerID; // defining the id that is assigned to the each register
    int whichRegisterIsAvailable; // defining in order to dedicate the register that a customer will be utilizing of 
// Here the function provides the determination of the available register for an upcoming customer and storing its index.
    int randomIndexFound = 0; //randomIndexFound behaves like a boolean variable which checks whether an available register is found
    while(randomIndexFound == 0){//loop for register allocation, if register[randomRegisterNumber] shows an unavailable register
        //then, new randomRegisterNumber should be generated, thus, loop is used here.  
        int randomRegisterNumber = rand() % (REGISTER_NUMBER);//generates an index number for register selection
        if(registers[randomRegisterNumber] == 0){//if the register is available
            whichRegisterIsAvailable = randomRegisterNumber;//the variable assigned to increase code readability
            randomIndexFound = 1;//making randomIndexFound 1 in order to terminate the loop, this means available register found
        }

    }
    registers[whichRegisterIsAvailable] = 1;  // The register that a customer is going to utilize is set here. 
	registerID = whichRegisterIsAvailable; // The current register ID is dedicated for the register that is available for an upcoming customer at the moment.
    
 
    

    printf("CUSTOMER %d GOES TO REGISTER %d.\n",customerID,registerID); // Printing the desired output
    int coffeeWaitingTime = rand() % (COFFEE_TIME_MAX-COFFEE_TIME_MIN+1) + COFFEE_TIME_MIN; // The time that a customer is held on a register is decided by a random number. 
	sleep(coffeeWaitingTime); // Then that thread customer gets made sleep according to that time.
    
   
    

    printf("CUSTOMER %d FINISHED BUYING FROM REGISTER %d AFTER %d SECONDS.\n",customerID,registerID,coffeeWaitingTime); // Printing the desired output

    registers[registerID] = 0; // Then that register is made available again here, so that another customer can utilize it
    sem_post(&semaphore); // Using the sem_post in order to increment the semaphore value by one.
    free(args); // The memory that is allocated before for the thread pointer gets deallocated thanks to this function.
}

int main(int argc, char *argv[]) {
    srand(time(NULL)); // this function is used to generate a random number, and in order to make it randomized each time the program is run, we have to pass the NULL parameter for the time.
    pthread_t th[CUSTOMER_NUMBER]; // defining the threads those who will be emerging as many as the amount of the customer number.
    sem_init(&semaphore, 0, REGISTER_NUMBER); // Here the semaphore's initiation with the amount of registers that will work with it. 
	int i; // An index variable in order to be used at the for loop iterating over the customers, namely, threads.

    for (i = 0; i < CUSTOMER_NUMBER; i++) { // There is a for loop in order to handle the creation of the customers, namely, threads. iterated by the defined amount of customers
        int* a = malloc(sizeof(int)); // The variable that will be set to create the customers enumeratedly is allocated in the memory dynamically, here.
        *a = i; // The variable value gotten from the iterator index value.
		int customerID = i; // This represents the customer's id that is about to be created according to the iterator index variable.
        int arrivingTime = rand() % (CUSTOMER_ARRIVAL_TIME_MAX-CUSTOMER_ARRIVAL_TIME_MIN+1)  + CUSTOMER_ARRIVAL_TIME_MIN; // This is the randomly created arriving time variable for 
		// the threads that are going to be created by the time ranged 1-3 seconds.
        sleep(arrivingTime); // And according to the randomly generated time, the thread sleeps.
        printf("CUSTOMER %d IS CREATED AFTER %d SECONDS.\n",customerID,arrivingTime); // Printing the desired output

        if (pthread_create(&th[i], NULL, &cafe, a) != 0) { // Here is the function for creating a thread, in the case that 0 is returned, a creation is succeeded
            perror("Thread creation failed!"); // Otherwise it outputs a failure about the thread creation.
        }

    }
    for (i = 0; i < CUSTOMER_NUMBER; i++) { // After all these, utilizing a for loop iterating as many as the amount of customers
        if (pthread_join(th[i], NULL) != 0) { // Threads are joined namely terminated here under the condition that 0 is returned.
            perror("Thread join failed!"); // Otherwise it outputs a failure about the thread termination
        }
    }
    sem_destroy(&semaphore); // This function is used for destroying the current semaphore that is created by the sem_init function, after all job is done.
    return 0; // exit successfully.
}
