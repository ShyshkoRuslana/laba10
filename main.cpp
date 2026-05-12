#include <iostream>
#include <thread>
#include <mutex>
#include "SafeQueue.h"
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

mutex m7;
mutex m8;
void thread7() {
    m7.lock();
    cout << "Thread 1 locked m1\n";
    this_thread::sleep_for(chrono::milliseconds(100));
    m8.lock();
    cout << "Thread 1 locked m2\n";
    m8.unlock();
    m7.unlock();
}

void thread8() {
    m8.lock();
    cout << "Thread 2 locked m2\n";
    this_thread::sleep_for(chrono::milliseconds(100));
    m7.lock();
    cout << "Thread 2 locked m1\n";
    m7.unlock();
    m8.unlock();
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
    t4.join();
    t5.join();
    cout << "Final counter: " << counter << endl;

    //tasak4
    thread t7(thread7);
    thread t8(thread8);
    t7.join();
    t8.join();

    //task5
    thread p(producer);
    thread c(consumer);
    p.join();
    c.join();


    return 0;
}