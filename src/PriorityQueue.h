/*
 * TaskPriorityQueue.h
 * Priority Queue for Task objects (sorted insert)
 */

#ifndef TASKPRIORITYQUEUE_H
#define TASKPRIORITYQUEUE_H

#include "Node.h"
#include "Task.h"
#include <stdexcept>

class TaskPriorityQueue {
private:
    Node<Task>* head;
    int size;

    // 優先度比較 (true → a の方が優先される)
    bool isHigherPriority(const Task& a, const Task& b) {
        if (a.getPriority() < b.getPriority()) return true;
        if (a.getPriority() > b.getPriority()) return false;
        // priority 同じなら deadline が短い方
        return a.getDeadline() < b.getDeadline();
    }

public:
    TaskPriorityQueue() {
        head = nullptr;
        size = 0;
    }

    ~TaskPriorityQueue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    bool isEmpty() const {
        return size == 0;
    }

    int getSize() const {
        return size;
    }

    void enqueue(const Task& task) {
        Node<Task>* newNode = new Node<Task>(task);

        // 先頭が空 or 新タスクの方が高優先度
        if (head == nullptr || isHigherPriority(task, head->data)) {
            newNode->next = head;
            head = newNode;
        } else {
            Node<Task>* current = head;
            // 挿入位置を探す
            while (current->next != nullptr &&
                   !isHigherPriority(task, current->next->data)) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
        size++;
    }

    Task dequeue() {
        if (isEmpty()) {
            throw std::runtime_error("PriorityQueue underflow");
        }
        Node<Task>* temp = head;
        Task task = temp->data;
        head = head->next;
        delete temp;
        size--;
        return task;
    }

    Task peek() const {
        if (isEmpty()) {
            throw std::runtime_error("PriorityQueue is empty");
        }
        return head->data;
    }
};

#endif // TASKPRIORITYQUEUE_H
