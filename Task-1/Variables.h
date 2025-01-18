#pragma once
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


void Thread_Mutex(int& id);
void MutexFunc(int countThreads);

void Thread_Semaphore(int& id);
void SemaphoreFunc(int countThreads);

void SemaphoreSlim_Acquire();
void SemaphoreSlim_Release();
void Thread_SemaphoreSlim(int& id);
void SemaphoreSlimFunc(int& threadCount);

void BarrierWait();
void Thread_Barrier(int id);
void BarrierFunc(int threadCount);

void SpinLock_Aquire();
void SpinLock_Release();
void Thread_Spinlock(int id);
void SpinlockFunc(int& threadCount);

void Treads_SpinWait(int id);
void SpinWaitFunc(int threadCount);

void Monitor_Acquire();
void Monitor_Release();
void Thread_Monitor(int id);
void MonitorFunc(int threadCount);







    






 
     
 