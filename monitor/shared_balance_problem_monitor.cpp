#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <stdarg.h>
#define RUNS 10000000 /* this value is large enough to cause a race condition */
#define TRANSFER_AMOUNT 1
using namespace std;

template <class C>
class Monitor {
  private:
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

  public:
    C slave;

    void run(void(C::*func)()) {
     /* gaining mutex */
      pthread_mutex_lock(&mutex);
     /* running func */
      void(C::*func_ptr)();
      func_ptr = func;
      (slave.*func_ptr)();
     /* releasing mutex */
      pthread_mutex_unlock(&mutex);
    };
};

class SharedBalance {
  private:
    long long balance;
  public:
    SharedBalance() {  
      balance = 0;
    }
    void credit() {balance += TRANSFER_AMOUNT;};
    void debit() {balance -= TRANSFER_AMOUNT;};

    long long getBalance() {return balance;};
};

Monitor<SharedBalance> m; /* global monitor */

void* creditor(void* arg) {
 for (int i = 0 ; i < RUNS ; i++){
  m.run(&SharedBalance::credit);
 } 
}

void* debitor(void* arg) {
 for (int i = 0 ; i < RUNS ; i++){
  m.run(&SharedBalance::debit);
 } 
}

int main() {
  pthread_t tid1, tid2;
  long long val1, val2;

  pthread_create(&tid1, NULL, creditor, NULL);
  pthread_create(&tid2, NULL, debitor, NULL);
  
  pthread_join(tid1, NULL); 
  pthread_join(tid2, NULL); 

  printf("Total is %lld\n", m.slave.getBalance());

  return 0;
}
