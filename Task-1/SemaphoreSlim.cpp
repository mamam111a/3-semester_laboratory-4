#include "Variables.h"

static int currentCountPermissions = 1;   
static int maxCountPermissions = 1;       
static mutex mutexObject;     
static condition_variable condVar; // условная переменная для уведомлений

// захват семафора
void SemaphoreSlim_Acquire() {
    unique_lock<mutex> lock(mutexObject); // захват мьютекса / lock guard не позволяет передавать управления другим функциям
    condVar.wait(lock, []() { return currentCountPermissions > 0; }); // Ожидаем, пока не появится разрешение
    currentCountPermissions--; 
}

// освобождение семафора
void SemaphoreSlim_Release() {
    unique_lock<mutex> lock(mutexObject);
    if (currentCountPermissions < maxCountPermissions) {
        currentCountPermissions++; 
        condVar.notify_one(); // уведомляем один из ожидающих потоков
    }
}

void Thread_SemaphoreSlim(int& id) {

    SemaphoreSlim_Acquire(); // захват семафора

    random_device randomSource;
    mt19937 generation(randomSource());
    uniform_int_distribution<> distribution(32, 126); 
    char symbol = static_cast<char>(distribution(generation));

    cout << "Поток " << ": " << symbol << endl;

    SemaphoreSlim_Release(); // освобождение семафора
}

void SemaphoreSlimFunc(int& threadCount) {

    vector<thread> threads;

    for (int i = 0; i < threadCount; i++) {
        threads.emplace_back(Thread_SemaphoreSlim, ref(i));//emplace аналог push_back,но не требует создания объекта перед вызовом
    }

    for (auto& object : threads) {
        object.join();// основной поток блокируется, пока каждый дочерний поток не завершится
    }
}

