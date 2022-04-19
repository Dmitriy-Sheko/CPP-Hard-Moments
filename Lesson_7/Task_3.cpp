#include "Task_3.h"
#include <numeric>

void Task_3()
{
    Task_2::FullName fn;
    fn.set_name("Dmitriy");
    fn.set_surname("Sheko");
    fn.set_patronymic("Vladimirovich");

    Task_2::Student s;
    *s.mutable_name() = fn;
    s.add_grades(5);
    s.add_grades(2);
    s.add_grades(4);
    s.add_grades(3);
    s.add_grades(4);
    s.add_grades(3);
    s.add_grades(4);
    s.add_grades(3);
    s.set_avg_score(std::accumulate(s.grades().begin(), s.grades().end(), 0) / s.grades().size());

    SG::StudentsGroup sg;
    sg.add_student(s);
    sg.Save();

    SG::StudentsGroup new_sg;
    new_sg.Open();
    std::cout << new_sg.GetAllInfo(fn) << std::endl;
}
