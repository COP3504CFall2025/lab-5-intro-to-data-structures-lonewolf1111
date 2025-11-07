#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLS : public StackInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLS() = default;

    // Insertion
    void push(const T& item) override {list.AddHead(item);}

    // Deletion
    T pop() override;

    // Access
    T peek() const override {return list.getHead()->data;}

    //Getters
    std::size_t getSize() const noexcept override {return list.getCount();}

    void PrintForward() {list.printForward();}
    void PrintReverse() {list.PrintReverse();}
};

// --------------------------Some code implementation here -----------------------------
template <typename T>
T LLS<T>::pop() {
    T temp = list.getHead()->data;
    list.RemoveHead();
    return temp-;
}