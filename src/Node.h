/*
 * Name: Mio Osawa
 * Id: 100405763
 * Instructor: Bita Shadgar
 * Section: 002
 */

#ifndef NODE_H
#define NODE_H

#include <string>
#include <iostream> 
using namespace std;

template <typename T>
class Node {
public:
    T data;
    Node<T>* next;
    Node<T> *prev;

    //use member initializer list for efficiency
    Node() : next(nullptr), prev(nullptr) {}

    Node(const T& t, Node<T>* n = nullptr, Node<T>* p = nullptr)
    : data(t), next(n), prev(p) {}
    
    // Node(){
    //     next = nullptr;
    //     prev = nullptr;
    // }
    // Node(const T& t, Node<T>* n = nullptr, Node<T>* p = nullptr) {
    //     data = t;
    //     next = n;
    //     prev = p;
    // }
};
#endif // NODE_H