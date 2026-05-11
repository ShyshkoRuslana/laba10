#include <iostream>
#include <thread>
#include <mutex>
using namespace std;
int counter=0;
mutex mtx;
void work(int thread_id){
    mtx.lock();
    for (int i = 0; i < 5; ++i) {
        counter += thread_id;
        cout<< "Thread: "<< thread_id << " Counter: " << counter << endl;
    }
    mtx.unlock();
}
int main(){

    thread t1([](int x){cout << "Square: " << x * x << endl;},2);
    thread t2([](int x){cout << "Square: " << x * x << endl;},3);
    thread t3([](int x){cout << "Square: " << x * x << endl;},4);
    t1.join();
    t2.join();
    t3.join();

    thread t4(work,1);
    thread t5(work,2);
    t4.join();
    t5.join();
    cout << "Final counter: " << counter << endl;

    return 0;
}