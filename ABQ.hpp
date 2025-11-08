#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABQ : public QueueInterface<T>{

    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;

public:
    // Constructors + Big 5
    ABQ();
    explicit ABQ(const size_t capacity);
    ABQ(const ABQ& other);
    ABQ& operator=(const ABQ& rhs);
    ABQ(ABQ&& other) noexcept;
    ABQ& operator=(ABQ&& rhs) noexcept;
    ~ABQ() noexcept;

    // Getters
    [[nodiscard]] size_t getSize() const noexcept override {return curr_size_;}
    [[nodiscard]] size_t getMaxCapacity() const noexcept {return capacity_;}
    [[nodiscard]] T* getData() const noexcept {return array_;}

    // Insertion
    void enqueue(const T& data) override;

    // Access
    T peek() const override;

    // Deletion
    T dequeue() override;

};

// ------------------------------------ Code implementation ------------------------------

//shrink if needed
//throw exceptions

template <typename T>
ABQ<T>::ABQ() {
    capacity_ = 1;
    curr_size_ = 0;
    array_ = new T[capacity_];
}

template <typename T>
ABQ<T>::ABQ(const size_t capacity) {
    capacity_ = capacity;
    curr_size_ = 0;
    array_ = new T[capacity_];
}

template <typename T>
T ABQ<T>::peek() const  {
    if (curr_size_ == 0) throw std::runtime_error("empty queue");
    return array_[0];
}

template <typename T>
void ABQ<T>::enqueue(const T& data) {
    // if(curr_size_ == capacity_) {
    //     capacity_ *= scale_factor_;
    //     T* temp = new T[capacity_];
    //     for (size_t i = 0; i < curr_size_; i ++) {
    //         temp[i] = array_[i];
    //     }
    //     delete[] array_;
    //     array_ = temp;
    //     temp = nullptr;
    // }
    
    array_[curr_size_++] = data;
}

template <typename T>
T ABQ<T>::dequeue() {
    if(curr_size_ == 0) throw std::runtime_error("empty queue");
    T temp = array_[0];
    // if(curr_size_ * scale_factor_ == capacity_) {
    //     capacity_ /= scale_factor_;
    //     T* resizedArray = new T[capacity_];
    //     for(size_t i = 0; i < curr_size_-1; i ++) {
    //         resizedArray[i] = array_[i + 1];
    //     }
    //     delete[] array_;
    //     array_ = resizedArray;
    //     resizedArray = nullptr;
    // } else {
        for(size_t i = 0; i < curr_size_-1; i ++) {
            array_[i] = array_[i+1];
        }
    // }
    curr_size_--;
    return temp;
}

//-----------------big 5---------------
template <typename T>
ABQ<T>::ABQ(const ABQ<T>& other) : capacity_(other.capacity_),curr_size_(other.curr_size_), array_(new T[other.curr_size_]){
    for(size_t i = 0; i < curr_size_; i ++) {
        array_[i] = other.array_[i];
    }
}

template <typename T>
ABQ<T>& ABQ<T>::operator=(const ABQ<T>& rhs) {
    if(this == &rhs) return *this;
    delete[] array_;
    T* temp = new T[rhs.capacity_];
    for(size_t i = 0; i < rhs.curr_size_; i ++) {
        temp[i] = rhs.array_[i];
    }
    capacity_ = rhs.capacity_;
    curr_size_ = rhs.curr_size_;
    array_ = temp;
    temp = nullptr;
    return *this;
}

template <typename T>
ABQ<T>::ABQ(ABQ<T>&& other) noexcept : capacity_(other.capacity_), curr_size_(other.curr_size_), array_(other.array_) {  
    delete[] other.array_;
    other.array_ = nullptr;
    other.capacity_ = 0;
    other.curr_size_ = 0;
}

template <typename T>
ABQ<T>& ABQ<T>::operator=(ABQ<T>&& rhs) noexcept {
    if (this == &rhs) return *this;
    array_ = rhs.array_;
    capacity_ = rhs.capacity_;
    curr_size_ = rhs.curr_size_;

    delete[] rhs.array_;
    rhs.array_ = nullptr;
    rhs.capacity_ = 0;
    rhs.curr_size_ = 0;
    return *this;
}

template <typename T>
ABQ<T>::~ABQ() noexcept{
    delete[] array_;
    array_ = nullptr;
    capacity_ = 0;
    curr_size_ = 0;
}