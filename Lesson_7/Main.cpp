#include <iostream>
#include <numeric>
#include <fstream>
#include "src-gen/Task_2.pb.h"
#include "Task_2.h"
#include "Task_3.h"

int main()
{
    Task_2::StudentsGroup sg;
    std::ifstream in("student.bin", std::ios_base::binary);
    if (sg.ParseFromIstream(&in))
    {
        std::cout << sg.students(0).name().surname() << std::endl;
        std::cout << sg.students(0).avg_score() << std::endl;
    }
    else
    {
        std::cout << "Error!" << std::endl;
    }
    Task_1_2();
    Task_3();

    return 0;
}

