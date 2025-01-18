#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <semaphore>
using namespace std;

const int countPhilosophers = 5;
mutex forks[countPhilosophers];
counting_semaphore<countPhilosophers> semaphore(countPhilosophers - 1); // только 4 философа
mutex coutMutex;  // для защиты вывода
void ChoicePhilosopher(int& id) {
    if(id == 0) cout << "\nФридрих Ницше ";
    if(id == 1) cout << "\nИммануил Кант ";
    if(id == 2) cout << "\nСократ ";
    if(id == 3) cout << "\nПлатон ";
    if(id == 4) cout << "\nАристотель ";
}
void Lunch(int id) {
    int leftFork = id;
    int rightFork = (id + 1) % countPhilosophers;

    while (true) {
        {
            lock_guard<mutex> lock(coutMutex);
            ChoicePhilosopher(id);
            cout << " размышляет" << endl;
        }
        this_thread::sleep_for(chrono::milliseconds(1000)); 

        semaphore.acquire(); // занимает место за столом

        // захват вилок
        {
            lock_guard<mutex> leftLock(forks[leftFork]);
            lock_guard<mutex> rightLock(forks[rightFork]);
            {
                lock_guard<mutex> lock(coutMutex);
                ChoicePhilosopher(id);
                cout << " ест" << endl;
            }
            this_thread::sleep_for(chrono::milliseconds(1000)); 
            {
                lock_guard<mutex> lock(coutMutex);  
                ChoicePhilosopher(id);
                cout <<" закончил есть" << endl;
            }
        }

        semaphore.release(); // уходит из-за стола
    }
}

int main() {
    setlocale(LC_ALL, "rus");
    vector<thread> philosophers;
    for (int i = 0; i < countPhilosophers; i++) {
        philosophers.emplace_back(Lunch, i);
    }
    for (auto& object : philosophers) {
        object.join();
    }
    return 0;
}
