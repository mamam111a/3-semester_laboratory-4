#include <iostream>
#include <thread>
#include <vector>
#include <random>
#include <mutex>
#include <condition_variable>
using namespace std;

static mutex mutexObject;

void Thread_Barrier(int id) {
    random_device randomSource;
    mt19937 generation(randomSource());
    uniform_int_distribution<> distribution(32, 126); 
    string symbol;
    symbol += static_cast<char>(distribution(generation));
     // Ожидание всех потоков на барьере
    this_thread::sleep_for(chrono::milliseconds(200));
    mutexObject.lock();
    cout << "Поток " << ": " << symbol << endl;
    mutexObject.unlock();
}

void BarrierFunc(int threadCount){
    vector<thread> threads; 
    for (int i = 0; i < threadCount; ++i) {
       threads.emplace_back(Thread_Barrier, i);
    }
    for (auto& object : threads) {
        object.join();  
    }
}