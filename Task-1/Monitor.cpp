#include "Variables.h"
static mutex mutexObject;
static condition_variable condVar;
static int counter = 0;
static const int maxCount = 2;  
void Monitor_Acquire() {
    unique_lock<mutex> lock(mutexObject);
    while (counter >= maxCount) {
        condVar.wait(lock);  // ожидание если максимальное количество потоков достигнуто
    }
    counter++;  // Увеличиваем счётчик занятых потоков
}

void Monitor_Release() {
    unique_lock<mutex> lock(mutexObject);
    counter--;  // Освобождаем ресурс уменьшаем счётчик
    condVar.notify_one();  // Уведомляем один из ожидающих потоков
}


void Thread_Monitor(int id) {
    Monitor_Acquire();  

    random_device randomSource;
    mt19937 generator(randomSource());
    uniform_int_distribution<> dist(32, 126);  

    char symbol = static_cast<char>(dist(generator));
    cout << "Поток " << ": " << symbol << endl;

    Monitor_Release();  
}

// Функция для запуска потоков
void MonitorFunc(int threadCount) {
    vector<thread> threads;

    for (int i = 0; i < threadCount; i++) {
        threads.emplace_back(Thread_Monitor, i);  
    }

    for (auto& object : threads) {
        object.join();
    }
}