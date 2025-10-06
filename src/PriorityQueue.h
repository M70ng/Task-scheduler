/*
 * PriorityQueue.h
 * Template-based Priority Queue implemented as a sorted linked list.
 * Lower priority number = higher priority.
 */

#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "Node.h"
#include <stdexcept>
#include <iostream>

template <typename T>
class PriorityQueue {
private:
    Node<T>* front;   // head = highest priority (lowest number)
    int size;

public:
    PriorityQueue() : front(nullptr), size(0) {}
    ~PriorityQueue() { clear(); }

    PriorityQueue(const PriorityQueue&) = delete;
    PriorityQueue& operator=(const PriorityQueue&) = delete;

    bool isEmpty() const { return front == nullptr; }
    int getSize() const { return size; }

    // Insert by priority (ascending order: 1, 2, 3, ...)
    void enqueue(const T& task) {
        Node<T>* newNode = new Node<T>(task);

        if (isEmpty() || task.getPriority() < front->data.getPriority()) {
            newNode->next = front;
            front = newNode;
        } else {
            Node<T>* current = front;
            while (current->next != nullptr &&
                   current->next->data.getPriority() <= task.getPriority()) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
        size++;
    }

    // Remove and return highest-priority task
    T dequeue() {
        if (isEmpty()) throw std::runtime_error("PriorityQueue underflow");
        Node<T>* temp = front;
        T task = temp->data;
        front = front->next;
        delete temp;
        size--;
        return task;
    }

    const T& peek() const {
        if (isEmpty()) throw std::runtime_error("PriorityQueue is empty");
        return front->data;
    }

    void clear() {
        while (!isEmpty()) dequeue();
    }

    void displayAll() const {
        if (isEmpty()) {
            std::cout << "[PriorityQueue is empty]\n";
            return;
        }
        Node<T>* current = front;
        while (current) {
            current->data.display();
            current = current->next;
        }
    }
};

#endif // PRIORITYQUEUE_H