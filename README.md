##Synchoronization PThread
The following is a collection of sychronization programs written in C using the PThread library.
The Goal is to demonstrate sychronization techniques.

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

### 

## Progress

## DeadLock
When two threads are stuck waiting for each other.

## Race Condition
Undetermenistic behaviour from threads.

## Priority Inversion.
When a higher priority thread waits behind a lower security one.

## Atomic operation

https://randu.org/tutorials/threads/
