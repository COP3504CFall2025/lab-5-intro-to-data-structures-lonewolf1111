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
    void pushFront(const T& item) override {list.addHead(item);}
    void pushBack(const T& item) override {list.addTail(item);}

    // Core Removal Operations
    T popFront() override;
    T popBack() override;

    // Element Accessors
    const T& front() const override;
    const T& back() const override;

    // Getter
    std::size_t getSize() const noexcept override {return list.getCount();}
    
    void PrintForward() {list.printForward();}
    void PrintReverse() {list.printReverse();}
};


// -------------------------------------Code Definition here ----------------------------------


template <typename T>
T LLDQ<T>::popFront() {
    if(!list.getHead()) {
        throw std::runtime_error("empty list");
    }
    T temp = front();
    list.removeHead();
    return temp;
}

template <typename T>
T LLDQ<T>::popBack() {
    if(!list.getHead()) {
        throw std::runtime_error("empty list");
    }
    T temp = back();
    list.removeTail();
    return temp;
}

template <typename T>
const T& LLDQ<T>::front() const {
    if(!list.getHead()) {
        throw std::runtime_error("empty list");
    }
    return list.getHead()->data;
}


template <typename T>
const T& LLDQ<T>::back() const {
    if(!list.getTail()) {
        throw std::runtime_error("empty list");
    }
    return list.getTail()->data;
}