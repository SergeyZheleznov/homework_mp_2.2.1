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

std::mutex m;

void GoToXY(short x, short y)
{
    SetConsoleCursorPosition(hStdOut, { x, y });
}

void draw(int a, int b)
{  
    int run_time = 0;
    // запускаем счётчик времени
    auto start1 = std::chrono::steady_clock::now();
    std::cout << "    " << a << "      " << std::this_thread::get_id() << std::endl;
    a = a + 2;
    int sleep_time1 = 500;
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time1));
    int sleep_time2 = 0;
    for (int i = 0; i < b; ++i) {           
        sleep_time2 = std::rand() % 1000;
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time2));
        m.lock();
        int x = 18 + i;
        GoToXY(x, a);
        std::cout << "*";
        m.unlock();
    }
    // замеряем время завершения работы
    auto finish1 = std::chrono::steady_clock::now();
    // здесь время работы программы от начала до конца
    auto diff1 = std::chrono::duration_cast<std::chrono::milliseconds>(finish1 - start1);
    // кладём время переменную
    run_time = diff1.count();
    std::cout << "       " << run_time << " ms" << std::endl;
        
}

int main()
{
    setlocale(LC_ALL, "ru");
    int quantity_streams = 0;
    int length_calculations = 0;
    int* run_time_1_stream = new int[4];

    std::cout << "Введите количество потоков " << std::endl;
   // std::cin >> quantity_streams;
    quantity_streams = 5;
 
    std::cout << "Введите длину расчётов " << std::endl;
    //std::cin >> length_calculations;
    length_calculations = 10;

    std::cout << "Номер п/п  " << " id " << "   Прогресс-бар " << " Время работы, ms " << std::endl;

    // создали коробку для потоков
    std::vector<std::thread> V;

    // здесь мы заполнили эту коробку, напихав туда с помощью метода пуш бэк, то есть вдавив последовательно, причём сначала первый, потом второй и так далее.
    //В скобках видно, что мы вкладываем потоки, и там функция и передаются значения переменных, всякий раз разные.
        for (int i = 0; i < quantity_streams; ++i)
        {
            V.push_back(std::thread(draw, i + 1, length_calculations));
        }

    // здесь мы все потоки последовательно запускаем.
    for (auto& el : V)
    {
        el.join();
    }

    return 0;
}

// вопросы по заданию
// какой символ использовать для того, чтобы полностью залить позицию символа?
// как сделать так, чтобы потоки выводились в порядке номеров?
