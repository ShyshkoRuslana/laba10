#ifndef LABA10_SAFEQUEUE_H
#define LABA10_SAFEQUEUE_H
#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
using namespace std;

class SafeQueue {
private:

    queue<int> q;

    mutex mtx;

    condition_variable cv;

public:

    void enqueue(int value) {

        unique_lock<mutex> lock(mtx);

        q.push(value);

        cout << "Produced: " << value << endl;

        cv.notify_one();
    }

    int dequeue() {

        unique_lock<mutex> lock(mtx);

        while (q.empty()) {

            cv.wait(lock);
        }

        int value = q.front();

        q.pop();

        return value;
    }
};

SafeQueue sq;

void producer() {

    for (int i = 1; i <= 5; i++) {

        sq.enqueue(i);

        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

void consumer() {

    for (int i = 1; i <= 5; i++) {

        int value = sq.dequeue();

        cout << "Consumed: " << value << endl;
    }

};


#endif
