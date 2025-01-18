#include "Variables.h"
static mutex mutexObject;
void Thread_Mutex(int& id) {

    random_device randomSource;
    mt19937 generation(randomSource());

    uniform_int_distribution <> distribution(32, 126);
    char symbol = static_cast<char>(distribution(generation));

    lock_guard<mutex> lock(mutexObject); //захват мьютекса
    cout << "Поток " << ": " << symbol << endl;
}

void MutexFunc(int countThreads) {
    vector<thread> threads;  

    for (int i = 0; i < countThreads; i++) {
        threads.emplace_back(Thread_Mutex, ref(i)); 
    }

    for (auto& object : threads) {
        object.join();  
    }
}
