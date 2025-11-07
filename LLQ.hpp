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
    void enqueue(const T& item) override {list.AddTail(item);} 

    // Deletion
    T dequeue() override;

    // Access
    T peek() const override {return list.getHead()->data;}

    // Getter
    std::size_t getSize() const noexcept override {return list.getCount();}

    void PrintForward() {list.printForward();}
    void PrintReverse() {list.PrintReverse();}


};
// -------------------------------------------Code implementation --------------------------------------
template <typename T>
T LLQ<T>::dequeue() {
    if(list.getTail() = nullptr) {
        throw std::runtime_error();
    }
    T temp = list.getTail()->data;
    list.RemoveTail();
    return temp;
}
template <typename T>
T LLQ<T>::peek() const  {
     if(list.getHead() = nullptr) {
        throw std::runtime_error();
    }
    return list.getHead()->data;
}
