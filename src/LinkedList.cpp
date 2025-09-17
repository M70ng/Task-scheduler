#include "LinkedList.h"
#include <iostream>
using namespace std;

LinkedList::LinkedList() {
    head = tail = nullptr;
    size = 0;
}

LinkedList::~LinkedList() {
    clear();
}

void LinkedList::insertTask(const Task& task) {
    Node<Task>* newNode = new Node<Task>(task);
    if (isEmpty()) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    size++;
}

bool LinkedList::deleteTask(const string& taskID) {
    if (isEmpty()) return false;

    Node<Task>* current = head;
    Node<Task>* previous = nullptr;

    while (current != nullptr && current->data.getTaskID() != taskID) {
        previous = current;
        current = current->next;
    }

    if (current == nullptr) return false; // 見つからなかった

    if (previous == nullptr) {
        // 先頭削除
        head = head->next;
        if (head == nullptr) tail = nullptr; // 空リストになった
    } else {
        previous->next = current->next;
        if (current == tail) {
            tail = previous; // tail更新
        }
    }

    delete current;
    size--;
    return true;
}

Task* LinkedList::findTask(const string& taskID) {
    Node<Task>* current = head;
    while (current != nullptr) {
        if (current->data.getTaskID() == taskID) {
            return &(current->data);
        }
        current = current->next;
    }
    return nullptr;
}

bool LinkedList::isEmpty() const {
    return head == nullptr;
}

int LinkedList::getSize() const {
    return size;
}

void LinkedList::clear() {
    while (head != nullptr) {
        Node<Task>* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
    size = 0;
}