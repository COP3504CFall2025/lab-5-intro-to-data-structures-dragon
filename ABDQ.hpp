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
    ABDQ() : capacity_(4), size_(0), front_(0), back_(0), data_(new T[4]) {}
    explicit ABDQ(std::size_t capacity) : capacity_(capacity), size_(0), front_(0), back_(0), data_(new T[capacity]) {}
    ABDQ(const ABDQ& other) : capacity_(other.capacity_), size_(other.size_), front_(other.front_), back_(other.back_), data_(new T[other.capacity_]) {
        for (size_t i = 0; i < size_; i++) {
            size_t index = (front_ + i) % capacity_;
            data_[index] = other.data_[index];
        }
    }
    ABDQ(ABDQ&& other) noexcept : capacity_(other.capacity_), size_(other.size_), front_(other.front_), back_(other.back_), data_(other.data_) {
        other.data_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;
    }
    ABDQ& operator=(const ABDQ& other) {
        if (this == &other) {
            return *this;
        }

        T* newData = new T[other.capacity_];
        for (size_t i = 0; i < other.size_; i++) {
            size_t index = (other.front_ + i) % other.capacity_;
            newData[index] = other.data_[index];
        }

        delete[] data_;
        data_ = newData;
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;

        return *this;
    }
    ABDQ& operator=(ABDQ&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        delete[] data_;
        data_ = other.data_;
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;

        other.data_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;

        return *this;
    }
    ~ABDQ() override {
        delete[] data_;
        data_ = nullptr;
        capacity_ = 0;
        size_ = 0;
        front_ = 0;
        back_ = 0;
    }

    // Insertion
    void pushFront(const T& item) override {
        if (size_ == capacity_) {
            ensureCapacity();
        }

        if (front_ == 0) {
            front_ = capacity_ - 1;
        }
        else {
            front_--;
        }

        data_[front_] = item;
        size_++;
    }
    void pushBack(const T& item) override {
        if (size_ == capacity_) {
            ensureCapacity();
        }

        data_[back_] = item;
        back_ = (back_ + 1) % capacity_;
        size_++;
    }

    // Deletion
    T popFront() override {
        if (size_ == 0) {
            throw std::runtime_error("The deque is empty");
        }

        T item = data_[front_];
        front_ = (front_  + 1) % capacity_;
        size_--;

        if (size_ <= capacity_/SCALE_FACTOR) {
            shrinkIfNeeded();
        }

        return item;
    }
    T popBack() override {
        if (size_ == 0) {
            throw std::runtime_error("The deque is empty");
        }

        back_ = (back_ == 0) ? capacity_ - 1 : back_ - 1;
        T item = data_[back_];
        size_--;

        if (size_ <= capacity_/SCALE_FACTOR) {
            shrinkIfNeeded();
        }

        return item;
    }

    // Access
    const T& front() const override {
        return data_[front_];
    }
    const T& back() const override {
        size_t index = (back_ == 0) ? capacity_ - 1 : back_ - 1;
        return data_[index];
    }

    // Getters
    std::size_t getSize() const noexcept override {
        return size_;
    }

    //Resizing
    void ensureCapacity() {
        T* newData = new T[capacity_ * SCALE_FACTOR];
        for (size_t i = 0; i < size_; i++) {
            size_t index = (front_ + i) % capacity_;
            newData[i] = data_[index];
        }

        delete[] data_;
        data_ = newData;
        capacity_ *= SCALE_FACTOR;
        front_ = 0;
        back_ = size_;
    }
    void shrinkIfNeeded() {
        T* newData = new T[capacity_ / SCALE_FACTOR];
        for (size_t i = 0; i < size_; i++) {
            size_t index = (front_ + i) % capacity_;
            newData[i] = data_[index];
        }

        delete[] data_;
        data_ = newData;
        capacity_ /= SCALE_FACTOR;
        front_ = 0;
        back_ = size_;
    }
};
