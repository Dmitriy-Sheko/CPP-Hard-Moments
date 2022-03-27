#include <iostream>
#include <string>
#include <optional>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>

using namespace std;


//   1.Создайте структуру Person с 3 полями: фамилия, имя, отчество.Поле отчество должно быть
//     опционального типа, т.к.не у всех людей есть отчество.Перегрузите оператор вывода данных
//     для этой структуры.Также перегрузите операторы < и == (используйте tie).

struct Person
{
    string firstname;
    string lastname;
    optional<string> patronymic;
};

optional<string> getOptStr(string& s)
{
    if (s == "")
    {
        return nullopt;
    }

    return s;
}

ostream& operator<<(ostream& out, const Person& p)
{
    out << setw(15) << p.firstname << setw(12) << p.lastname;

    if (p.patronymic.has_value())
    {
        out << setw(17) << p.patronymic.value();
    }
    else
    {
        out << setw(18);
    }

    return out;
}

bool operator<(const Person& p1, const Person& p2)
{
    return tie(p1.firstname, p1.lastname, p1.patronymic) < tie(p2.firstname, p2.lastname, p2.patronymic);
}

bool operator==(const Person& p1, const Person& p2)
{
    return tie(p1.firstname, p1.lastname, p1.patronymic) == tie(p2.firstname, p2.lastname, p2.patronymic);
}


//   2.Создайте структуру PhoneNumber с 4 полями:
//     · код страны(целое число)
//     · код города(целое число)
//     · номер(строка)
//     · добавочный номер(целое число, опциональный тип)
//     Для этой структуры перегрузите оператор вывода.Необходимо, чтобы номер телефона
//     выводился в формате : +7(911)1234567 12, где 7 – это номер страны, 911 – номер города,
//     1234567 – номер, 12 – добавочный номер.Если добавочного номера нет, то его выводить не
//     надо.Также перегрузите операторы < и == (используйте tie)

struct PhoneNumber
{
    int country_code;
    int city_code;
    string number;
    optional<int> additional_number;
};

bool operator<(const PhoneNumber& p1, const PhoneNumber& p2)
{
    return tie(p1.country_code, p1.city_code, p1.number, p1.additional_number) < tie(p2.country_code, p2.city_code, p2.number, p2.additional_number);
}

optional<int> getOptInt(string& s)
{
    if (s == "")
    {
        return nullopt;
    }

    return stoi(s);
}

ostream& operator<<(ostream& out, const PhoneNumber& p)
{
    out << setw(3) << '+' << p.country_code << '(' << p.city_code << ')' << p.number;

    if (p.additional_number.has_value())
    {
        out << ' ' << p.additional_number.value();
    }

    return out;
}


//   3.Создайте класс PhoneBook, который будет в контейнере хранить пары : Человек – Номер
//     телефона.Конструктор этого класса должен принимать параметр типа ifstream – поток данных,
//     полученных из файла.В теле конструктора происходит считывание данных из файла и
//     заполнение контейнера.Класс PhoneBook должен содержать перегруженный оператор
//     вывода, для вывода всех данных из контейнера в консоль

class PhoneBook
{
private:
    vector<pair<Person, PhoneNumber>> m_data;
public:
    PhoneBook(ifstream& file)
    {
        if (!file)
        {
            cout << "Не удаётся открыть файл!" << endl;
            exit(-1);
        }

        for (string line; getline(file, line);)
        {
            stringstream str(line);
            vector<string> rowData;

            for (string s; getline(str, s, ';');)
            {
                rowData.push_back(s);
            }

            pair<Person, PhoneNumber> entry;

            for (size_t i = 0; i < rowData.size(); ++i)
            {
                switch (i)
                {
                case 0:
                    entry.first.firstname = rowData[i];
                    break;
                case 1:
                    entry.first.lastname = rowData[i];
                    break;
                case 2:
                    entry.first.patronymic = getOptStr(rowData[i]);
                    break;
                case 3:
                    entry.second.country_code = stoi(rowData[i]);
                    break;
                case 4:
                    entry.second.city_code = stoi(rowData[i]);
                    break;
                case 5:
                    entry.second.number = rowData[i];
                    break;
                case 6:
                    entry.second.additional_number = getOptInt(rowData[i]);
                    break;
                }
            }

            m_data.push_back(entry);
        }
    }

    friend ostream& operator<<(ostream& out, const PhoneBook& pb)
    {
        for (const auto& [first, second] : pb.m_data)
        {
            out << first << ' ' << second << endl;
        }

        return out;
    }

    void SortByName()
    {
        sort(m_data.begin(), m_data.end(), [](const pair<Person, PhoneNumber>& lhs, const pair<Person, PhoneNumber>& rhs)
            {
                return lhs.first < rhs.first;
            });
    }

    void SortByPhone()
    {
        sort(m_data.begin(), m_data.end(), [](const pair<Person, PhoneNumber>& lhs, const pair<Person, PhoneNumber>& rhs)
            {
                return lhs.second < rhs.second;
            });
    }

    pair<string, vector<PhoneNumber>> GetPhoneNumber(const string& firstname)
    {
        vector<PhoneNumber> phoneNumbers;
        int count = 0;

        for_each(m_data.begin(), m_data.end(), [&](const auto& entry)
            {
                if (entry.first.firstname == firstname)
                {
                    phoneNumbers.push_back(entry.second);
                    ++count;
                }
            });

        switch (count)
        {
        case 0:
            return { "not found", phoneNumbers };
        case 1:
            return { "", phoneNumbers };
        default:
            return { "found more than 1", phoneNumbers };
        }
    }

    void ChangePhoneNumber(const Person& p, const PhoneNumber& pn)
    {
        auto entry = find_if(m_data.begin(), m_data.end(), [&](const auto& entry)
            {
                return entry.first == p;
            });

        if (entry != m_data.end())
        {
            entry->second = pn;
        }
    }
};

int main()
{
    ifstream file("PhoneBook.txt");
    PhoneBook book(file);
    cout << book;

    cout << "------SortByPhone-------" << endl;
    book.SortByPhone();
    cout << book;

    cout << "------SortByName--------" << endl;
    book.SortByName();
    cout << book;

    cout << "-----GetPhoneNumber-----" << endl;
    // лямбда функция, которая принимает фамилию и выводит номер телефона этого человека, либо строку с ошибкой
    auto print_phone_number = [&book](const string& surname)
    {
        cout << surname << "\t";
        auto answer = book.GetPhoneNumber(surname);
        if (get<0>(answer).empty())
        {
            for (size_t i = 0; i < get<1>(answer).size(); ++i)
            {
                cout << get<1>(answer)[i];
            }
        }
        else
        {
            cout << get<0>(answer);
        }
        cout << endl;
    };
    // вызовы лямбды
    print_phone_number("Ivanov");
    print_phone_number("Petrov");

    cout << "----ChangePhoneNumber----" << endl;
    book.ChangePhoneNumber(Person{ "Kotov", "Vasilii", "Eliseevich" }, PhoneNumber{ 7, 123, "15344458", nullopt });
    book.ChangePhoneNumber(Person{ "Mironova", "Margarita", "Vladimirovna" }, PhoneNumber{ 16, 465, "9155448", 13 });
    cout << book;

    return 0;
}
