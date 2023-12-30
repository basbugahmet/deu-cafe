# General Information

The purpose of this assignment is to create a simulation of a cafe using POSIX threads, mutexes, and semaphores. The simulation involves customers arriving at the cafe, attempting to find an open register, placing orders, and receiving their coffee. The program is designed to handle multiple customers and registers, and the timing of customer arrivals and coffee preparation is randomized within specified bounds.


# Key components and functionalities

1.  **Global Static Variables:**
    
    -   `CUSTOMER_NUMBER`: Specifies the total number of customers the program should handle.
    -   `CUSTOMER_ARRIVAL_TIME_MIN` and `CUSTOMER_ARRIVAL_TIME_MAX`: Define the minimum and maximum time, respectively, between customer arrivals.
    -   `REGISTER_NUMBER`: Indicates the number of registers the program should manage.
    -   `COFFEE_TIME_MIN` and `COFFEE_TIME_MAX`: Establish the minimum and maximum waiting times for ordering and receiving coffee by customers.
2.  **Simulation Steps:**
    
    -   Customers are created at random intervals defined by `CUSTOMER_ARRIVAL_TIME_MIN` and `CUSTOMER_ARRIVAL_TIME_MAX`.
    -   Customers attempt to find an open register, and if none are available, they wait until one becomes vacant.
    -   After finding an empty register, customers place their orders, and the coffee preparation process takes a random amount of time defined by `COFFEE_TIME_MIN` and `COFFEE_TIME_MAX`.
    -   Outputs are provided in the terminal (CLI) to inform the user of the ongoing processes, including customer creation, register selection, and the time taken to complete the purchase.
3.  **Output Examples:**
    
    -   `CUSTOMER <CUSTOMER_ID> IS CREATED AFTER <TIME> SECONDS.`
        -   Indicates the creation of a customer with the specified ID after waiting for a random time.
    -   `CUSTOMER <CUSTOMER_ID> GOES TO REGISTER <REGISTER_ID>.`
        -   Informs that a customer with the given ID is at a specific register, initiating the ordering process.
    -   `CUSTOMER <CUSTOMER_ID> FINISHED BUYING FROM REGISTER <REGISTER_ID> AFTER <TIME> SECONDS.`
        -   Notifies when a customer has completed the purchase from a particular register, specifying the time taken.

The overall objective is to implement a multi-threaded simulation of a cafe where customers interact with registers to order and receive coffee. The program uses POSIX threads, mutexes, and semaphores to manage the concurrent execution of these processes.
