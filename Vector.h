#pragma once
 
template <class T>
class Vector
{
    T* arr;
    int size;
    int capacity;

    void Delete()
    {
        delete[] arr;
        arr = nullptr;
    }

public:
    Vector() : arr(nullptr), size(0), capacity(0) {}
    Vector(const int s) : arr(new T[s]), size(0), capacity(s) {}
    Vector(const Vector& arrayToCopy) : size(arrayToCopy.size)
    {
        arr = new T[size];

        for (int i = 0; i < size; i++)
            arr[i] = arrayToCopy.arr[i];
    }

    void push_back(const T& x)
    {
        if (arr != nullptr)
        {
            if (size < capacity)
            {
                arr[size] = x;
                size++;
            }
            else
            {
                capacity *= 2;
                T* temp = new T[capacity];
                for (int i = 0; i < size; i++)
                    temp[i] = arr[i];
                temp[size] = x;
                Delete();
                arr = temp;
                size++;
            }
        }
        else
        {
            capacity += 1;
            arr = new T[capacity];
            arr[size] = x;
            size++;
        }
    }
    void pop(int x = 1)
    {
        if (x < 0)
            x = 0;

        size -= x;
        if (size < 0)
            size = 0;
    }
    void clear()
    {
        Delete();
        size = 0;
        capacity = 0;
    }
    void redact(int x)
    {
        if (x >= size)
            x = size - 1;
        if (x < 0)
            x = 0;

        for (int i = x; i < size - 1; i++)
            arr[i] = arr[i + 1];
        arr[size - 1] = T(0);

        size--;
    }
    T& operator[](int x)
    {
        return arr[x];
    }
    void insert(const T& x, int idx)
    {
        if (idx < 0 || idx > size - 1)
            throw std::out_of_range("Index out of range in insert()");

        push_back(x);

        T temp = arr[size - 1];
        for (int i = size - 2; i >= idx ; i--)
            arr[i + 1] = arr[i];

        arr[idx] = temp;
    }

    const T& operator[](int x) const
    {
        return arr[x];
    }

    int getSize() const
    {
        return size;
    }
    T* getArray() const
    {
        return arr;
    }

    bool isNUll() const
    {
        return (arr == nullptr);
    }
    int getCapacity() const
    {
        return capacity;
    }
    ~Vector()
    {
        Delete();
    }
};