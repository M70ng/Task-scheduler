/*
 * Stack.h
 * A simple linked-list based Stack implementation
 */

#ifndef STACK_H
#define STACK_H

#include "Node.h"
#include <stdexcept>

template <typename T>
class Stack {
private:
    Node<T>* top;
    int size;

public:
    Stack() {
        top = nullptr;
        size = 0;
    }

    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    bool isEmpty() const {
        return size == 0;
    }

    int getSize() const {
        return size;
    }

    void push(const T& val) {
        Node<T>* newNode = new Node<T>(val);
        newNode->next = top;
        top = newNode;
        size++;
    }

    T pop() {
        if (isEmpty()) {
            throw std::runtime_error("Stack underflow");
        }
        Node<T>* temp = top;
        T value = temp->data;
        top = top->next;
        delete temp;
        size--;
        return value;
    }

    T peek() const {
        if (isEmpty()) {
            throw std::runtime_error("Stack is empty");
        }
        return top->data;
    }
};

#endif // STACK_H