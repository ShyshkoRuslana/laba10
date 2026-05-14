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
        cv.wait(lock, [this] { return q.size() < 5; });
        q.push(value);
        cout << "Produced: " << value << endl;
        cv.notify_one();
    }

    int dequeue() {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [this] { return !q.empty(); });
        int value = q.front();
        q.pop();
        cv.notify_all();
        return value;
    }
};
SafeQueue sq;
void producer() {
    for (int i = 1; i <= 5; i++) {
        sq.enqueue(i);
    }
}
void consumer() {
    for (int i = 1; i <= 5; i++) {
        int value = sq.dequeue();
        cout << "Consumed: " << value << endl;
    }
};


#endif
