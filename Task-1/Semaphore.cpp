#include "Variables.h"
static counting_semaphore<2> SemaphoreObject(2);  // разрешает одновременно работать только 2 потокам

void Thread_Semaphore(int& id) {
    // захват семафора
    SemaphoreObject.acquire();

    random_device randomSource;
    mt19937 generation(randomSource());

    uniform_int_distribution <> distribution(32, 126);

    char symbol = static_cast<char>(distribution(generation));

    cout << "Поток " << ": " << symbol << endl;

    // освобождение семафора
    SemaphoreObject.release();
}

void SemaphoreFunc(int countThreads) {
    vector<thread> threads;
    for (int i = 0; i < countThreads; i++) {
        threads.emplace_back(Thread_Semaphore, ref(i));//emplace аналог push_back,но не требует создания объекта перед вызовом
    }
    for (auto& object: threads) { 
        object.join();// основной поток блокируется, пока каждый дочерний поток не завершится
    }
}
    
