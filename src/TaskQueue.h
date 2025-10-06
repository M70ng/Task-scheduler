 /*
 * Name: Mio Osawa
 * Id: 100405763
 * Instructor: Bita Shadgar
 * Section: 002
 * 
 * TaskQueue.h
 * Queue for completed Task objects
 */

#ifndef TASKQUEUE_H
#define TASKQUEUE_H

#include "Node.h"
#include "Task.h"
#include <stdexcept>

class TaskQueue {
private:
    Node<Task>* front;
    Node<Task>* rear;
    int size;

public:
    TaskQueue() {
        front = rear = nullptr;
        size = 0;
    }

    ~TaskQueue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    // Deep copy constructor
    TaskQueue(const TaskQueue& other) {
        front = rear = nullptr;
        size = 0;
        Node<Task>* cur = other.front;
        while (cur) {
            enqueue(cur->data);
            cur = cur->next;
        }
    }

    // Deep copy assignment
    TaskQueue& operator=(const TaskQueue& other) {
        if (this == &other) return *this;
        // clear existing
        while (!isEmpty()) dequeue();
        Node<Task>* cur = other.front;
        while (cur) {
            enqueue(cur->data);
            cur = cur->next;
        }
        return *this;
    }

    // Clear all elements
    void clear() {
        while (!isEmpty()) dequeue();
    }

    bool isEmpty() const {
        return size == 0;
    }

    int getSize() const {
        return size;
    }

    void enqueue(const Task& task) {
        Node<Task>* newNode = new Node<Task>(task);
        if (isEmpty()) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        size++;
    }

    Task dequeue() {
        if (isEmpty()) {
            throw std::runtime_error("TaskQueue underflow");
        }
        Node<Task>* temp = front;
        Task task = temp->data;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        delete temp;
        size--;
        return task;
    }

    Task peek() const {
        if (isEmpty()) {
            throw std::runtime_error("TaskQueue is empty");
        }
        return front->data;
    }
};

#endif // TASKQUEUE_H
