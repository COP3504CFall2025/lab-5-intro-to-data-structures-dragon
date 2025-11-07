#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLS : public StackInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLS() : list() {}

    // Insertion
    void push(const T& item) override {
        list.AddHead(item);
    }

    // Deletion
    T pop() override {
        if (list.GetCount() == 0) {
            throw std::runtime_error("The stack is empty");
        }
        T item = list.GetHead()->data;
        list.RemoveHead();

        return item;
    }

    // Access
    T peek() const override {
        if (list.GetCount() == 0) {
            throw std::runtime_error("The stack is empty");
        }

        return list.GetHead()->data;
    }

    // Getters
    std::size_t getSize() const noexcept override {
        return list.GetCount();
    }
};