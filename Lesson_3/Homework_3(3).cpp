//   3.Реализовать собственный класс итератора, с помощью которого можно будет
//     проитерироваться по диапазону целых чисел в цикле for - range - based.


#include <iostream>
#include <iomanip>
#include "Task_2.h"
#include "Task_3.h"

using namespace std;


void Task_3()
{
    Matrix m(4);
    m.fillRandom();

    for (const double& i : m)
    {
        cout << setw(5) << i;
    }

    cout << endl;
}
