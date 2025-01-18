#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <mutex>
using namespace std;

struct Date {
    int day;
    int month;
    int year;
};

bool CheckCorrectDate(const Date& date) {
    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; //невисокосный год
    if (date.month < 1 || date.month > 12)
        return false;

    int daysInCurrentMonth = daysInMonth[date.month - 1]; //убираем единицу для нумерации с 1 в месяцах

    if (date.month == 2 && (date.year % 4 == 0 && date.year % 100 != 0) || (date.year % 400 == 0)) //проверка на високосный год
        daysInCurrentMonth = 29;

    return date.day >= 1 && date.day <= daysInCurrentMonth;
}

void VerificationCycle(const vector<Date>& dates, vector<Date>& invalidDates, int start, int end) {
    for (int i = start; i < end; i++) {
        if (!CheckCorrectDate(dates[i])) {
            invalidDates.push_back(dates[i]);
        }
    }
}

void ProcessDatesSequential(vector<Date>& dates) {
    vector<Date> invalidDates;
    for (auto& date : dates) {
        if (!CheckCorrectDate(date)) {
            invalidDates.push_back(date);
        }
    }

    cout << "Incorrect dates: " << invalidDates.size() << endl;
    for (auto& date : invalidDates) {
        cout << date.day << "/" << date.month << "/" << date.year << endl;
    }
}

void ProcessChunk(int start, int end, const vector<Date>& dates, vector<Date>& invalidDates) {
    for (int j = start; j < end; j++) {
        if (!CheckCorrectDate(dates[j])) {
            invalidDates.push_back(dates[j]);
        }
    }
}

void ProcessDatesParallel(vector<Date>& dates, int numThreads) {
    int chunkSize = dates.size() / numThreads; // разделение труда по размерам для потоков
    vector<thread> threads;
    vector<vector<Date>> allInvalidDates(numThreads); // Вектор для хранения результатов по каждому потоку

    for (int i = 0; i < numThreads; i++) {
        int start = i * chunkSize;
        int end = (i == numThreads - 1) ? dates.size() : start + chunkSize;

        threads.push_back(thread(ProcessChunk, start, end, ref(dates), ref(allInvalidDates[i])));
    }

    for (auto& object : threads) {
        object.join();
    }

    vector<Date> invalidDates;
    for (auto& threadPart : allInvalidDates) {
        invalidDates.insert(invalidDates.end(), threadPart.begin(), threadPart.end());
    }

    cout << "Incorrect dates: " << invalidDates.size() << endl;
    for (auto& date : invalidDates) {
        cout << date.day << "/" << date.month << "/" << date.year << endl;
    }
}


int main() {
    setlocale(LC_ALL, "rus");
    vector<Date> dates(1000000, {31, 12, 2024});  
    dates.push_back({32, 12, 2024});  // Неправильная дата (32 декабря)
    dates.push_back({30, 2, 2024});   // Неправильная дата (февраль не может иметь 30 дней в 2024 году)
    dates.push_back({31, 4, 2024});   // Неправильная дата (апрель имеет 30 дней)
    dates.push_back({0, 7, 2023});    // Неправильная дата (день не может быть 0)
    dates.push_back({31, 11, 2023});  // Неправильная дата (ноябрь имеет 30 дней)

    int numThreads = 10;

    auto start = chrono::high_resolution_clock::now();
    ProcessDatesSequential(dates);
    auto end = chrono::high_resolution_clock::now();
    auto differenceSequential = chrono::duration<double>(end - start).count();
    cout << "Замер времени без многопоточности " << differenceSequential << " секунд"<<endl;

    start = chrono::high_resolution_clock::now();
    ProcessDatesParallel(dates, numThreads);
    end = chrono::high_resolution_clock::now();
    auto differenceParallel = chrono::duration<double>(end - start).count();
    cout << "Замер времени с использованием многопоточности: " << differenceParallel << " секунд" << endl;

    return 0;
}