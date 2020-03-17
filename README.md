

## Design Patterns
- Different design patterns work best for different situations
- Threads incur overhead

### Thread Pool (Boss/Worker)
A (Boss) thread forks other (worker) threads to perform useful tasks.  These threads are part of a pre-designated pool. 

### Peer (Workscrew)
Identical to 'Thread Pool' DP except the Boss thread becomes a worker after the pool is created.

### Pipeline

