#include <iostream>
#include <thread>

using namespace std;
int main(){

    thread t1([](int x){cout << "Square: " << x * x << endl;},2);
    thread t2([](int x){cout << "Square: " << x * x << endl;},3);
    thread t3([](int x){cout << "Square: " << x * x << endl;},4);

    t1.join();
    t2.join();
    t3.join();
    return 0;
}