#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABS : public StackInterface<T> {
public:
    // Big 5 + Parameterized Constructor
    ABS(); 
    explicit ABS(const size_t capacity);
    ABS(const ABS& other);
    ABS& operator=(const ABS& rhs);
    ABS(ABS&& other) noexcept;
    ABS& operator=(ABS&& rhs) noexcept;
    ~ABS() noexcept;

    // Get the number of items in the ABS
    [[nodiscard]] size_t getSize() const noexcept override {return curr_size_;}

    // Get the max size of the ABS
    [[nodiscard]] size_t getMaxCapacity() const noexcept {return capacity_;}

    // Return underlying data for the stack
    [[nodiscard]] T* getData() const noexcept {return array_;}

    // Push item onto the stack
    void push(const T& data) override;

    T peek() const override;

    T pop() override;
    //less than or equal to capacity over 4
    //shrinkIfNeeded
private:
    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;
};

// ---------------------------------Implementation here-------------------------------------------------------
template <typename T>
ABS<T>::ABS() {
    capacity_ = 1;
    curr_size_ = 0;
    array_ = new T[capacity_];
}

template <typename T>
ABS<T>::ABS(const size_t capacity) {
    capacity_ = capacity;
    curr_size_ = 0;
    array_ = new T[capacity_];
}

template <typename T>
ABS<T>:: ~ABS() noexcept{
    delete[] array_;
    array_ = nullptr;
    curr_size_ = 0;
    capacity_ = 0;
}

template <typename T>
ABS<T> :: ABS(const ABS& other) : capacity_(other.capacity_),curr_size_(other.curr_size_), array_(new T[other.capacity_]){
    for(size_t i = 0; i < other.curr_size_; i ++) {
        array_[i] = other.array_[i];
    }
}

template <typename T>
ABS<T>& ABS<T>::operator=(const ABS<T>& rhs) {
    if(this == &rhs) return *this;
    delete[] array_;
    T* temp = new T[rhs.capacity_]; 
    for(size_t i = 0; i < rhs.curr_size_; i ++) {
        temp[i] = rhs.array_[i];
    }
    curr_size_ = rhs.curr_size_;
    capacity_ = rhs.capacity_;
    array_ = temp;
    temp = nullptr;
    return *this;
}

template <typename T> 
ABS<T>::ABS(ABS&& other) noexcept : capacity_(other.capacity_), curr_size_(other.curr_size_), array_(other.array_) {
    other.array_ = nullptr;
    other.capacity_ = 0;
    other.curr_size_ = 0;
}

template <typename T>
ABS<T>& ABS<T>::operator=(ABS&& rhs) noexcept {
    if (this == &rhs) return *this;
    delete[] array_;
    array_ = rhs.array_;
    capacity_ = rhs.capacity_;
    curr_size_ = rhs.curr_size_;
    
    rhs.array_ = nullptr;
    rhs.capacity_ = 0;
    rhs.curr_size_ = 0;
    
    return *this;
}


//big 5 looks str8, idk bout these member functions
template <typename T>
void ABS<T>::push(const T& data) {
    if(curr_size_ == capacity_) {
        capacity_ *= scale_factor_;        
        T* resizedArray = new T[capacity_];
        for(size_t i = 0; i < curr_size_; i ++) {
            resizedArray[i] = array_[i];
        }
        
        delete[] array_;
        array_ = resizedArray;
        resizedArray = nullptr;
    }
    array_[curr_size_] = data;
    curr_size_ ++;
}

template <typename T>
T ABS<T>::pop() {
    if(curr_size_ == 0) throw std::runtime_error("Empty Stack");
    if(curr_size_ * scale_factor_ == capacity_) {
        capacity_ /= scale_factor_;
        T* resizedArray = new T[capacity_];
        for(size_t i = 0; i < curr_size_; i ++) {
            resizedArray[i] = array_[i];
        }
        
        delete[] array_;
        array_ = resizedArray;
        resizedArray = nullptr;
    }
    T temp = array_[--curr_size_];
    return temp;
}

template <typename T> 
T ABS<T>::peek() const {
    if (curr_size_ == 0) throw std::runtime_error("Empty Stack");
    size_t sizes = curr_size_-1;
    return array_[sizes];
}