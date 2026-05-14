#include <iostream>
#include <thread>
#include <mutex>
#include "SafeQueue.h"
#include "Task4.h"
using namespace std;
int counter=0;
mutex mtx;
void work(int thread_id){
    for (int i = 0; i < 5; ++i) {
        mtx.lock();
        counter += thread_id;
        cout<< "Thread: "<< thread_id << " Counter: " << counter << endl;
        mtx.unlock();
    }

}
int main(){
    //task1
    thread t1([](int x){cout << "Square: " << x * x << endl;},2);
    thread t2([](int x){cout << "Square: " << x * x << endl;},3);
    thread t3([](int x){cout << "Square: " << x * x << endl;},4);
    t1.join();
    t2.join();
    t3.join();

    //task2-3
    thread t4(work,1);
    thread t5(work,2);
    thread t6(work,3);
    t4.join();
    t5.join();
    t6.join();
    cout << "Final counter: " << counter << endl;

    //task4
    thread t7(Task4);
    t7.join();

    //task5
    thread p(producer);
    thread c(consumer);
    p.join();
    c.join();




    return 0;
}