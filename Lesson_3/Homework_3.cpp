//   1.Написать функцию, добавляющую в конец списка вещественных чисел
//     элемент, значение которого равно среднему арифметическому всех его
//     элементов.



#include <iostream>
#include "Task_1.h"
using namespace std;

void printList(list<float>& l)
{
    cout << "{ ";

    for (list<float>::const_iterator iter = l.begin(); iter != l.end(); ++iter)
    {
        cout << *iter << (next(iter, 1) == l.end() ? " " : ", ");
    }

    cout << '}' << endl;
}

void pushBackList(list<float>& l)
{
    float sum = 0;

    for (const float& value : l)
    {
        sum += value;
    }

    l.push_back(sum / l.size());
}

void Task_1()
{
    list<float> l{ 54.46, 43.32, 37.89, 19.99 };
    size_t countCycle = 15;

    for (size_t i = 0; i < countCycle; ++i)
    {      
        if (i % 5 == 0)
        {
            printList(l);
        }

        pushBackList(l);
    }

    printList(l);
}

