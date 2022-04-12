#pragma once
#include <iostream>
#include <iterator>
#include <string>
#include <unordered_set>
#include <vector>
#include <list>
#include <deque>

template<typename IT>
void printWords(IT it, IT end)
{
    std::unordered_set<std::string> countWords(it, end);
    std::copy(countWords.begin(), countWords.end(), std::ostream_iterator<std::string>(std::cout, "; "));
}

void Task_1()
{
    std::vector<std::string> v{ "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Four", "Eight", "Nine", "One", "Four" };
    std::cout << "Vector output:" << std::endl;
    printWords(v.begin(), v.end());

    std::list<std::string> l(v.begin(), v.end());
    std::cout << "\List output:" << std::endl;
    printWords(l.begin(), l.end());

    std::deque<std::string> d(v.begin(), v.end());
    std::cout << "\Deck output:" << std::endl;
    printWords(d.begin(), d.end());
}
