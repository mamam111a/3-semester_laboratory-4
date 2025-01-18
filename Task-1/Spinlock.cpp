#include "Variables.h"
static atomic_flag spinlock = ATOMIC_FLAG_INIT;

void SpinLock_Aquire() {
    while (spinlock.test_and_set(memory_order_acquire)) { //memory_order_acquire  - поток "захватывает" все операции которые были сделаны до этого в другом потоке
        //цикл продолжает выполняться пока блокировка не освободится
    }
}

void SpinLock_Release() {
    spinlock.clear(memory_order_release); // memory_order_release -поток "освобождает" все свои действия, чтобы другие потоки могли увидеть их в правильном порядке
}

void Thread_Spinlock(int id) {

    SpinLock_Aquire();

    random_device randomSource;
    mt19937 generation(randomSource());
    uniform_int_distribution<> distribution(32, 126);  
    char symbol = static_cast<char>(distribution(generation));

    cout << "Поток " << ": " << symbol << endl;

    SpinLock_Release();
}

void SpinlockFunc(int& threadCount) {
    vector<thread> threads;

    for (int i = 0; i < threadCount; i++) {
        threads.emplace_back(Thread_Spinlock, i);
    }

    for (auto& object : threads) {
        object.join();
    }
}



