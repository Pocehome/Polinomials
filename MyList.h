#include <iostream>

template <typename T>
class MyList {
private:
    T* arr;                // Internal array for storing elements
    size_t length;          // Field for storing list length
    size_t capacity;        // Field for storing the current capacity of the array

public:
    // Constructor
    MyList(size_t initCapacity = 100) : arr(new T[initCapacity]), length(0), capacity(initCapacity) {}

    // Destructor
    ~MyList() {
        delete[] arr;
    }

    // Adding an element to the end of a list
    void push_back(const T& value) {
        if (length == capacity) {
            // Increase the array capacity by 100
            T* newArr = new T[capacity + 100];
            for (size_t i = 0; i < length; i++) {
                newArr[i] = arr[i];
            }
            delete[] arr;
            arr = newArr;
            capacity += 100;
        }
        arr[length] = value;
        length++;
    }

    // Getting a constant element by index
    const T& operator[](size_t index) const {
        if (index >= length) {
            throw std::out_of_range("Index out of range");
        }
        return arr[index];
    }

    // Getting an element by index
    T& operator[](size_t index) {
        if (index >= length) {
            throw std::out_of_range("Index out of range");
        }
        return arr[index];
    }

    // Erase an element by index
    void erase(size_t index) {
        if (index >= length) {
            throw std::out_of_range("Index out of range");
        }
        for (size_t i = index; i < length - 1; i++) {
            arr[i] = arr[i + 1];
        }
        length--;
    }

    // Getting the length of a list
    size_t getLength() const {
        return length;
    }
};
