#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* data_;                 // underlying dynamic array
    std::size_t capacity_;    // total allocated capacity
    std::size_t size_;        // number of stored elements
    std::size_t front_;       // index of front element
    std::size_t back_;        // index after the last element (circular)

    static constexpr std::size_t SCALE_FACTOR = 2;

public:
    // Big 5
    ABDQ();
    explicit ABDQ(std::size_t capacity);
    ABDQ(const ABDQ& other);
    ABDQ(ABDQ&& other) noexcept;
    ABDQ& operator=(const ABDQ& other);
    ABDQ& operator=(ABDQ&& other) noexcept;
    ~ABDQ() ;

    // Insertion
    void pushFront(const T& item) override;
    void pushBack(const T& item) override;

    // Deletion
    T popFront() override;
    T popBack() override;

    // Access
    const T& front() const override;
    const T& back() const override;

    // Getters
    std::size_t getSize() const noexcept override { return size_;};

};

template <typename T>
ABDQ<T>::ABDQ() {
    capacity_ = 4;
    size_ = 0;
    front_ = 0;
    back_ = 0;
    data_ = new T[capacity_];
}


template <typename T>
ABDQ<T>::ABDQ(std::size_t capacity) {
    capacity_ = capacity;
    size_ = 0;
    front_ = 0;
    back_ = 0;
    data_ = new T[capacity_];
}

template <typename T>
const T& ABDQ<T>::front() const{
    return data_[front_];
}

template <typename T>
const T& ABDQ<T>::back() const{
    return data_[back_-1];
}

// <------------------------------------- Big 5 shi -------------------------------------->
template <typename T>
ABDQ<T>::ABDQ(const ABDQ<T>& other) {
    T* temporary = new T[other.capacity_];
    for(size_t i = 0; i < other.size_; i ++) {
        temporary[i] = other[i];
    }
    data_ = temporary;
    temporary = nullptr;
    capacity_  = other.capacity_;
    size_ = other.size_;
    front_ = other.front_;
    back_ = other.back_;
    
}

template <typename T>
ABDQ<T>& ABDQ<T>::operator=(const ABDQ<T>& rhs) {
    if (this == &rhs) return *this;
    delete[] data_;
    T* temporary = new T[rhs.capacity_];
    
    for(size_t i = 0; i < rhs.size_; i ++) {
        temporary[i] = rhs[i];
    }
    data_ = temporary;
    temporary = nullptr;

    capacity_ = rhs.capacity_;
    size_ = rhs.size_;
    front_ = rhs.front_;
    back_ = rhs.back_;

    return *this;
}

template <typename T>
ABDQ<T>::ABDQ(ABDQ<T>&& other) noexcept : data_(other.data_), capacity_(other.capacity_), 
    size_(other.size_), front_(other.front_), back_(other.back_){
        other.data_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;
}

template <typename T>
ABDQ<T>& ABDQ<T>::operator=(ABDQ<T>&& rhs) noexcept {
    if (this == &rhs) return *this;
    delete[] data_;
    data_ = rhs.data_;
    capacity_ = rhs.capacity_;
    size_ = rhs.size_;
    front_ = rhs.front_;
    back_ = rhs.back_;

    rhs.data_ = nullptr;
    rhs.capacity_ = 0;
    rhs.size_ = 0;
    rhs.front_ = 0;
    rhs.back_ = 0;

    return *this;
}

template <typename T>
ABDQ<T>::~ABDQ() {
    delete[] data_;
    capacity_ = 0;
    size_ = 0;
    front_ = 0;
    back_ = 0;
}