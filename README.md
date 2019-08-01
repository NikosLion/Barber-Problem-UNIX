This was a homework for the Operating Systems course in Computer Science.

The barber's problem is a common synchronization problem in operating systems.

This is my solution to this problem using UNIX's pthreads and semaphores.
There are two threads (barbers or grocers) serving a number of clients
(also threads) which is defined by the user. The user also tells the program 
how many chairs are available for the clients to wait until they can be served.

If a client arrives and no chair is available he then leaves. The program
keeps account of how many clients were actually served and how many had to
leave unserved.

The time that each (served) customer had to wait is also calculated and an
average is given as output.
