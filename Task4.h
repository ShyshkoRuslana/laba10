#ifndef TASK4_H
#define TASK4_H
#include <iostream>
#include <thread>
#include <mutex>
using namespace std;
mutex m7;
mutex m8;
void thread7() {
    lock_guard<mutex> lock(m7);
    this_thread::yield();
    lock_guard<mutex> lock2(m8);
}

void thread8() {
    lock_guard<mutex> lock(m8);
    this_thread::yield();
    lock_guard<mutex> lock2(m7);
}

void Task4() {
    thread t7(thread7);
    thread t8(thread8);
    t7.join();
    t8.join();

};


#endif
