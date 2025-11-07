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
    T peek() const override {return list.getHead();}

    //Getters
    std::size_t getSize() const noexcept override {return list.getCount();}

    void printForward() {list.PrintForward();}
    void printReverse() {list.PrintReverse();}
};

// --------------------------Some code implementation here -----------------------------
template <typename T>
T LLS<T>::pop() {
    T temp = list.getHead();
    list.RemoveHead();
    return temp;
}