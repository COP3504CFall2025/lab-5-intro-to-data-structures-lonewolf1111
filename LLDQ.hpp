#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <utility>



template <typename T>
class LLDQ : public DequeInterface<T> {
private:
    LinkedList<T> list;

public:
    // Constructor
    LLDQ() = default;

    // Core Insertion Operations
    void pushFront(const T& item) override {list.AddHead(item);}
    void pushBack(const T& item) override {list.AddTail(item);}

    // Core Removal Operations
    T popFront() override;
    T popBack() override;

    // Element Accessors
    const T& front() const override {return list.getHead()->data;}
    const T& back() const override {return list.getTail()->data;}

    // Getter
    std::size_t getSize() const noexcept override {return list.getCount();}
    
    void PrintForward() {list.PrintForward();}
    void PrintReverse() {list.PrintReverse();}
};


// -------------------------------------Code Definition here ----------------------------------


template <typename T>
T LLDQ<T>::popFront() {
    T temp = front();
    list.RemoveHead();
    return temp;
}

template <typename T>
T LLDQ<T>::popBack() {
    T temp = back();
    list.RemoveTail();
    return temp;
}
