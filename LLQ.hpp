#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLQ : public QueueInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLQ() = default;

    // Insertion
    void enqueue(const T& item) override {list.addTail(item);}
    // Deletion
    T dequeue() override;

    // Access
    T peek() const override ;

    // Getter
    std::size_t getSize() const noexcept override {return list.getCount();}

    void PrintForward() {list.printForward();}
    void PrintReverse() {list.PrintReverse();}


};
// -------------------------------------------Code implementation --------------------------------------
template <typename T>
T LLQ<T>::dequeue() {
    if(!list.getTail()) {
        throw std::runtime_error("empty list");
    }
    T temp = list.getTail()->data;
    list.removeTail();
    return temp;
}


template <typename T>
T LLQ<T>::peek() const {
    if(!list.getTail()) {
        throw std::runtime_error("empty list");
    }
    return list.getHead()->data;
}