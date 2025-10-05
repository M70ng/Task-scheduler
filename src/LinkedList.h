#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <string>
#include "Node.h"
using namespace std;

template <typename T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;

public:
    LinkedList();               
    ~LinkedList();              

    void insertTask(const T& task);   
    bool deleteTask(const string& taskID); 
    Node<T>* findTask(const string& taskID) const;

    bool isEmpty() const;
    int getSize() const;
    void clear();
    void displayAll() const;

    Node<T>* getHead() const { return head; }
    Node<T>* getTail() const { return tail; }
};

template <typename T>
LinkedList<T>::LinkedList() {
    head = tail = nullptr;
    size = 0;
}

template <typename T>
LinkedList<T>::~LinkedList() {
    clear();
}

template <typename T>
bool LinkedList<T>::isEmpty() const {
    return head == nullptr;
}

template <typename T>
int LinkedList<T>::getSize() const {
    return size;
}

template <typename T>
void LinkedList<T>::insertTask(const T& t) {
    Node<T>* newNode = new Node<T>(t);
    if (isEmpty()) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    size++;
}

template <typename T>
bool LinkedList<T>::deleteTask(const string& taskID) {
    if (isEmpty()) return false;

    Node<T>* current = head;
    while (current != nullptr && current->data.getTaskID() != taskID) {
        current = current->next;
    }

    if (!current) return false; // not found

    if (current == head) head = head->next;
    if (current == tail) tail = tail->prev;
    if (current->prev) current->prev->next = current->next;
    if (current->next) current->next->prev = current->prev;

    delete current;
    size--;
    return true;
}

template <typename T>
Node<T>* LinkedList<T>::findTask(const string& taskID) const {
    Node<T>* current = head;
    while (current != nullptr) {
        if (current->data.getTaskID() == taskID)
            return current;
        current = current->next;
    }
    return nullptr;
}

template <typename T>
void LinkedList<T>::clear() {
    Node<T>* current = head;
    while (current != nullptr) {
        Node<T>* temp = current;
        current = current->next;
        delete temp;
    }
    head = tail = nullptr;
    size = 0;
}

template <typename T>
void LinkedList<T>::displayAll() const {
    if (isEmpty()) {
        cout << "No tasks available.\n";
        return;
    }

    Node<T>* current = head;
    while (current != nullptr) {
        current->data.display();
        current = current->next;
    }
}

#endif // LINKEDLIST_H