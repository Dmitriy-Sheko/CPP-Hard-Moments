#pragma once
#include <cstddef>

class Matrix
{
private:
    const size_t matrixSize;
    const size_t matrixCapacity;
    double* array;
    double matrixDeterminant{ 0.0 };

    Matrix getModifiedMatrix(Matrix& arr, const size_t item);
    double calculateDeterminant(Matrix& arr);
public:
    Matrix(const int size);
    void fillRandom();             
    void print() const;            
    size_t size() const;               
    double determinant() const;        
    class Iterator
    {
    private:
        double* current;
    public:
        Iterator(double* pointer);
        double& operator[](size_t i);
        Iterator& operator ++();
        bool operator !=(const Iterator& iterator);
        double& operator *();
    };

    Iterator operator[](size_t i);
    Iterator begin();
    Iterator end();

    ~Matrix();
};

void Task_2();

