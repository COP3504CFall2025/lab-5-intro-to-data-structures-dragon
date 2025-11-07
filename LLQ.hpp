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
    LLQ() : list() {}

    // Insertion
    void enqueue(const T& item) override {
        list.AddTail(item);
    }

    // Deletion
    T dequeue() override {
        if (list.getCount() == 0) {
            throw std::runtime_error("The queue is empty");
        }

        T item = list.getHead()->data;
        list.RemoveHead();
        return item;
    }

    // Access
    T peek() const override {
        if (list.getCount() == 0) {
            throw std::runtime_error("The queue is empty");
        }

        return list.getHead()->data;
    }

    // Getter
    std::size_t getSize() const noexcept override {
        return list.getCount();
    }

};