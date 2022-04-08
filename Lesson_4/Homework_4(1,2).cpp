//   1.Имеется отсортированный массив целых чисел.Необходимо разработать функцию
//     insert_sorted, которая принимает вектор и новое число и вставляет новое число в
//     пределенную позицию в векторе, чтобы упорядоченность контейнера сохранялась.
//     Реализуйте шаблонную функцию insert_sorted, которая сможет аналогично работать с любым
//     контейнером, содержащим любой тип значения.


#include <iostream>
#include <vector>
#include <list>
#include <math.h>
#include <algorithm>
#include "Tasks.h"
#include "Templates.h"

using namespace std;


void Task_1()
{
    const unsigned int size = 10;
    int newIntValue = -3;
    double newDoubleValue = 2.2;

    vector<int> v(size);
    generator(v, -10, 10);
    sort(v.begin(), v.end());
    print(v);                             
    insert_sorted(v, newIntValue);
    print(v);                             
    cout << endl;

    list<double> l(size);
    generator(l, -10.0, 10.0);
    l.sort();
    print(l);                             
    insert_sorted(l, newDoubleValue);
    print(l);                             
    cout << endl;
}


//   2.Сгенерируйте вектор a, состоящий из 100 вещественный чисел, представляющий собой
//     значения аналогового сигнала.На основе этого массива чисел создайте другой вектор целых
//     чисел b, представляющий цифровой сигнал, в котором будут откинуты дробные части чисел.
//     Выведите получившиеся массивы чисел.Посчитайте ошибку, которой обладает цифровой
//     сигнал по сравнению с аналоговым по формуле :
//     ,
//     𝑖 = 0
//     𝑁−1
//     ∑(𝑎𝑖 − 𝑏𝑖)2
//     где :
//     N - количество элементов в векторе,
//     a - элемент вектора с дробными числами,
//     b - элемент вектора с целыми числами
//     Постарайтесь воспользоваться алгоритмическими функциями, не используя циклы


void Task_2()
{
    vector<double> v(100);

    double error = 0;
    generator(v, -1000.0, 1000.0);

    print(v);                                                        
    copy(v.begin(), v.end(), ostream_iterator<int> { cout, " " });    
    cout << endl;

    for_each(v.begin(), v.end(), [&](const double& i)
        {
            error += pow(i - static_cast<int>(i), 2);
        });

    cout << endl << "Ошибка, которой обладает цифровой сигнал по сравнению с аналоговым: " << error << endl;
}


int main()
{
    Task_1();
    Task_2();

    return 0;
}