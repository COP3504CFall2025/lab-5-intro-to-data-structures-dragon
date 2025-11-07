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
        assert(list.GetHead() != nullptr);
        if (list.GetCount() == 0) {
            throw std::runtime_error("The queue is empty");
        }

        T item = list.GetHead()->data;
        list.RemoveHead();
        return item;
    }

    // Access
    T peek() const override {
        if (list.GetCount() == 0) {
            throw std::runtime_error("The queue is empty");
        }

        return list.GetHead()->data;
    }

    // Getter
    std::size_t getSize() const noexcept override {
        return list.GetCount();
    }

};