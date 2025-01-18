#include "Variables.h"

static atomic<int> atomicCounter(0);  
  
static const int maxCount = 3;   

void Treads_SpinWait(int id) {
    while (atomicCounter.load(std::memory_order_acquire) >= maxCount) { //load читает из атомарной 
        //memory_order_acquire  - поток "захватывает" все операции которые были сделаны до этого в другом потоке
        this_thread::yield();  // ожидание с уступкой процессора другим потокам из стандартной библиотекки thread
    }

    atomicCounter.fetch_add(1, memory_order_acquire);  // fetch_add выполняет атомарное увеличение значения атомарной переменной на 1

    random_device randomSource;
    mt19937 generation(randomSource());
    uniform_int_distribution<> distribution(32, 126);  

    char symbol = static_cast<char>(distribution(generation));
    cout << "Поток " << ": " << symbol << endl;

    atomicCounter.fetch_sub(1, memory_order_release);
}

void SpinWaitFunc(int threadCount) {
    vector<thread> threads;

    for (int i = 0; i < threadCount; i++) {
        threads.emplace_back(Treads_SpinWait, i);
    }

    for (auto& object : threads) {
        object.join();
    }
}

