// homework_mp_2.2.1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//Задание 2
//Прогресс - бар

//Создайте консольное приложение для имитации многопоточного расчёта.
//Количество потоков, длина расчёта должны быть заданы переменными.
//В консоль во время работы программы должны построчно для каждого потока выводиться :

//• номер потока по порядку;
//• идентификатор потока;
//• заполняющийся индикатор наподобие прогресс - бара, визуализирующий процесс «расчёта»;
//• после завершения работы каждого потока в соответствующей строке суммарное время, затраченное на работу потока.

//Строки прогресс - баров каждого потока должны выводиться одновремено.Время появления каждого нового символа 
//в строке прогресс - бара подберите так, чтобы процесс заполнения строки был виден.Пример работы программы по ссылке.
/*
#include <iostream>
#include <thread>
#include <execution>
#include <algorithm>
#include <random>
#include <chrono>
#include <vector>
#include <cmath>
#include <windows.h>
#include <mutex>

using namespace std::chrono_literals;

std::mutex m;

void func1()
{
    int run_time_1_stream = 0;
    auto start1 = std::chrono::steady_clock::now();

    for (int i = 0; i < 10; ++i)
    {
        std::this_thread::sleep_for(1000ms);
        m.lock();
        std::cout <<  "_";   
        m.unlock();
    }
        // замеряем время завершения работы
        auto finish1 = std::chrono::steady_clock::now();
        // здесь время работы программы от начала до конца
        auto diff1 = std::chrono::duration_cast<std::chrono::milliseconds>(finish1 - start1);
        // кладём время в массив
        run_time_1_stream = diff1.count();
        std::cout << "    " << run_time_1_stream << std::endl;
}
void func2()
{
    int run_time_2_stream = 0;
    auto start2 = std::chrono::steady_clock::now();

    for (int i = 0; i < 10; ++i)
    {
        std::this_thread::sleep_for(1000ms);
        m.lock();
        std::cout << "_";
        m.unlock();
    }
    // замеряем время завершения работы
    auto finish2 = std::chrono::steady_clock::now();
    // здесь время работы программы от начала до конца
    auto diff2 = std::chrono::duration_cast<std::chrono::milliseconds>(finish2 - start2);
    // кладём время в массив
    run_time_2_stream = diff2.count();
    std::cout << "    " << run_time_2_stream << std::endl;
}

int main()
{
    setlocale(LC_ALL, "ru");
    int quantity_streams = 0;
    int length_calculations = 0;
    int* run_time_1_stream = new int[4];

    std::cout << "Введите количество потоков " << std::endl;
   // std::cin >> quantity_streams;
    quantity_streams = 2;
 
    std::cout << "Введите длину расчётов " << std::endl;
    //std::cin >> length_calculations;
    length_calculations = 10;

    std::cout << "Номер п/п  " << " Идентицикатор потока " << " Прогресс-бар " << " Время работы потоков, ms " << std::endl;
    std::cout << "    " << quantity_streams << "         " << std::this_thread::get_id();
   
    std::cout << "    " << 1 << "         " << std::this_thread::get_id();
    std::cout << "    " << 2 << "         " << std::this_thread::get_id();
    std::cout << "               ";
    std::cout << "               ";
    std::thread t1(func1);
    std::thread t2(func2);
    t1.join();
    t2.join();

    return 0;
}
*/
#include <iostream>
#include <thread>
#include <chrono>


void DoWork()
{
    for (size_t i = 0; i < 10; ++i)
    {
        std::cout << "ID потока = " << std::this_thread::get_id() << " DoWork    " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}
int main()
{
    setlocale(LC_ALL, "ru");

    std::thread th1(DoWork);
    std::thread th2(DoWork);
  
    for (size_t i = 0; i < 10; ++i)
    {
        std::cout << "ID потока = " << std::this_thread::get_id() << "  main   " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
     th1.join();
     th2.join();
    return 0;
}