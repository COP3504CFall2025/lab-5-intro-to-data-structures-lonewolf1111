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

    void PrintForward() {list.PrintForward();}
    void PrintReverse() {list.PrintReverse();}


};
// -------------------------------------------Code implementation --------------------------------------
template <typename T>
T LLQ<T>::dequeue() {
    T temp = list.getTail();
    list.RemoveTail();
    return temp->data;
}