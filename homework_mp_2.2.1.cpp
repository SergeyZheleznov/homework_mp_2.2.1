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

#include <iostream>
#include <thread>
#include <execution>
#include <chrono>
#include <vector>
#include <windows.h>
#include <mutex>
#include <conio.h>

using namespace std::chrono_literals;
using namespace std;

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

std::mutex m1;
std::mutex m2;

void GoToXY(short x, short y)
{
    SetConsoleCursorPosition(hStdOut, { x, y });
}

void draw0(int a)
{
    for (int i = 0; i < a; i++)
    {
        std::cout << i << std::endl;
    }

}

void draw1(int a, int b)
{   
   
    m1.lock();
    short x = 7;
    short y = a + 3;
    GoToXY(x, y);
    
    std::cout << std::this_thread::get_id() << std::endl;
    SetConsoleCursorPosition(hStdOut, { x, y });

    x = 14;
    y = 3;
    
    
    m1.unlock();

    int sleep_time0 = 1500;
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time0));
    int run_time = 0;
    a = a + 3;
    auto start1 = std::chrono::steady_clock::now();
    
    int sleep_time2 = 0;
    for (int i = 0; i < b; ++i) {
        
        sleep_time2 = std::rand() % 1000;
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time2));
        m2.lock();

        x = 15 + i;
        GoToXY(x, a);
        
        std::cout << (char)219;
        m2.unlock();
    }

    // замеряем время завершения работы
    auto finish1 = std::chrono::steady_clock::now();
    // здесь время работы программы от начала до конца
    auto diff1 = std::chrono::duration_cast<std::chrono::milliseconds>(finish1 - start1);
    // кладём время переменную
    run_time = diff1.count();

    int sleep_time1 = 1500;
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time1));
    x = 35;
    y = a;
    GoToXY(x, y);

    std::cout << run_time << " ms" << std::endl;
    x = 35;
    y = a;
    GoToXY(x, y);
}

int main()
{
    int quantity_streams = 4;
    int length_calculations = 10;
    int* run_time_1_stream = new int[4];

    std::cout << "Print quantity of streams " << quantity_streams << std::endl;
 
    std::cout << "Print length of calculation " << length_calculations << std::endl;

    std::cout << "Number  " << " id " << "   Progress-bar " << "      time, ms " << std::endl;

    draw0(quantity_streams);

    thread* t = new thread[quantity_streams];
   
    for (int i = 0; i < quantity_streams; i++)
    {
        t[i] = thread(draw1, i, length_calculations);
    }
    for (int i = 0; i < quantity_streams; i++)
    {
        t[i].join();
    }
    int x = 10;
    int y = 10;
    GoToXY(x, y);


    return 0;
}

