## Synchoronization PThread
The following is a collection of sychronization programs written in C using the PThread library.
The Goal is to demonstrate sychronization techniques.

### fork() vs pthread_create() 
While both fork() and pthread_create() create new threads.  fork() creates a completely new process with it's own address space, source code, and stack to go with the new thread.  The forked process and the parent process will both execute the next line of code after the fork() after initialization.
pthread_create() on the other hand creates a new thread under the calling process.  The new thread gets it's own stack and thread ID but shares will share it's virtual address space, open files, signal handlers, user and group IDs.  Therefore it is possible to communicate between threads created using pthread_create() using shared memory.

As synchronization issues arise due to the use of shared memory I will be using pthread_create() to create my threads.

## What is Synchronization?
Ensuring that independent processes/threads begin to execute a designated block of code at the same logical time.

## Design Patterns
- Different design patterns work best for different situations
- Threads incur overhead
- Minimizing time spend within Critical Sections increaces concurrency.

### Thread Pool (Boss/Worker)
A (Boss) thread forks other (worker) threads to perform useful tasks.  These threads are part of a pre-designated pool. 

### Peer (Workscrew)
Identical to 'Thread Pool' DP except the Boss thread becomes a worker after the pool is created.

### Pipeline
Each thread forks a child which in turn forks a child.

## Mutual Exclusion
Multiple threads often need to touch a shared section of data.  However manipulation of said data at the exact same time would cause problems.  
Therefore mutual exclusion techniques are applied to ensure only one thread accesses a 'Critical Section' at a time.  Ex:
- Accessing a var being written would yield an outdated version
- Two threads modifying the same var at the same time would yield an unpredicatble result

### Mutex (Lock)
Before being granded to a C.S. (Critical Section) a thread must first gain the mutex.  Any other programs
attempting to access the lock will be denied.  Then when the thread is done it releases the mutex allowing another thread to take it.
A mutex can be imagined as a lock with only one key.  When a thread gains a mutex it is taking the sole key for the lock and unlocking it's lock.
Other threads cannot unlock their locks because the key is in use.  Only when the mutex is released are the other threads free to open their locks. 

### Semaphore
If a Mutex is a lock then a semaphore is a traffic light.  A 'binary semaphore' is essentially identical to a mutex but a counting semaphore can count values above 1.  When a semaphore

V(s): {s = s+1} 
P(s): [while(s == 0) {wait}; s = s-1]

## Progress

## DeadLock
When two threads are stuck waiting for each other.

## Nondeterminacy (Race Condition)
Undetermenistic behaviour from threads or order of execution changes result.

## Priority Inversion.
When a higher priority thread waits behind a lower security one.

## Atomic operation

https://randu.org/tutorials/threads/
https://stackoverflow.com/questions/5514464/difference-between-pthread-and-fork-on-gnu-linux
man clone
man fork
man pthread_create
