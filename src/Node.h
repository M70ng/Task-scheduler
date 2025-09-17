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
    Node(){
        next = nullptr;
    }
    Node(const T& t){
        data = t;
        next = nullptr;
    }
};
#endif // NODE_H