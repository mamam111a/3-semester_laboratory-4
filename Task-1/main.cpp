#include <iostream>
#include <thread>
#include <vector>
#include <random>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <barrier>
#include <semaphore>
using namespace std;
#include "Variables.h"

int main() {
    int threadCount = 12;

    cout << "Мьютекс:" << endl;
    auto start = chrono::high_resolution_clock::now();
    MutexFunc(threadCount);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration<double>(end - start).count();
    cout << "Время: " << duration << " секунд" << endl << endl;

    cout << "Семафор:" << endl;
    start = chrono::high_resolution_clock::now();
    SemaphoreFunc(threadCount);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration<double>(end - start).count();
    cout << "Время: " << duration << " секунд" << endl << endl;

    cout << "СемафорСлим:" << endl;
    start = chrono::high_resolution_clock::now();
    SemaphoreSlimFunc(threadCount);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration<double>(end - start).count();
    cout << "Время: " << duration << " секунд" << endl << endl;

    cout << "Барьер:" << endl;
    start = chrono::high_resolution_clock::now();  
    BarrierFunc(threadCount); 
    end = chrono::high_resolution_clock::now(); 
    long long totalSleepTime = 200;
    duration = chrono::duration<double>(end - start).count();
    auto cleanTime = (totalSleepTime - duration) / 1000.0;  
    cout << "Время: " << cleanTime << " секунд" << endl << endl;  

    cout << "Спинлок:" << endl;
    start = chrono::high_resolution_clock::now();
    SpinlockFunc(threadCount);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration<double>(end - start).count();
    cout << "Время: " << duration << " секунд" << endl << endl;

    cout << "Спинвэит:" << endl;
    start = chrono::high_resolution_clock::now();
    SpinWaitFunc(threadCount);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration<double>(end - start).count();
    cout << "Время: " << duration << " секунд" << endl << endl;

    cout << "Монитор:" << endl;
    start = chrono::high_resolution_clock::now();
    MonitorFunc(threadCount);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration<double>(end - start).count();
    cout << "Время: " << duration << " секунд" << endl << endl;

    return 0;
}
