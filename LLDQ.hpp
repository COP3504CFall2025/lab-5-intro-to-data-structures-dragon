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
    LLDQ() : list() {}

    // Core Insertion Operations
    void pushFront(const T& item) override {
        list.AddHead(item);
    }
    void pushBack(const T& item) override {
        list.AddTail(item);
    }

    // Core Removal Operations
    T popFront() override {
        if (list.GetCount() == 0) {
            throw std::runtime_error("The deque is empty");
        }

        T item = list.GetHead()->data;
        list.RemoveHead();
        return item;
    }
    T popBack() override {
        if (list.GetCount() == 0) {
            throw std::runtime_error("The deque is empty");
        }

        T item = list.GetTail()->data;
        list.RemoveTail();
        return item;
    }

    // Element Accessors
    const T& front() const override {
        if (list.GetCount() == 0) {
            throw std::runtime_error("The deque is empty");
        }

        return list.GetHead()->data;
    }
    const T& back() const override {
        if (list.GetCount() == 0) {
            throw std::runtime_error("The deque is empty");
        }

        return list.GetTail()->data;
    }

    // Getter
    std::size_t getSize() const noexcept override {
        return list.GetCount();
    }
};






