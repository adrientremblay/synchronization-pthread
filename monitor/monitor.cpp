#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;

#define RUNS 10000000 /* this value is large enough to cause a race condition */

template <class C>
class Monitor {
  private:
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    C slave;

  public:
    void run(void(C::*func)()) {
      void(C::*func_ptr)();
      func_ptr = func;
      (slave.*func_ptr)();
    };
};

class SharedBalance {
  public:
    int balance;  
    void credit(int amount) {balance += amount; std:cout << "hello";};
    void debit(int amount) {balance -= amount;};
    void test() {std:cout << "fuck";};
};

void* count(void* arg);

/* shared global variable */
long long total = 0;

/* add value to total RUNS times  */
void* count(void* arg) {
  long long value = *(long long*) arg;

  for (int i = 0 ; i < RUNS ; i++) {
    /* end critcal section */ 

    total += value;
    
    /* end critcal section */ 
  }
  
  pthread_exit(0);
}

int main() {
  /* pthread_t tid1, tid2; */
  /* long long val1, val2; */
  /* val1 = 1; */
  /* val2 = -1; */ 

  /* pthread_create(&tid1, NULL, count, &val1); */
  /* pthread_create(&tid2, NULL, count, &val2); */
  
  /* pthread_join(tid1, NULL); */ 
  /* pthread_join(tid2, NULL); */ 

  /* printf("Total is %lld\n", total); */
  
  Monitor<SharedBalance> m;
  m.run(&SharedBalance::test);

  return 0;
}
