//  Node* current

// Node* head

#ifndef ITERATOR_H
#define ITERATOR_H

#include <iostream>
#include "Node.h"
#include <climits>
using namespace std;

template <typename T>
class Iterator{
    private:
        Node* current;
    public:
        Iterator(Node* start): current(start) {}
        bool hasNext();
        Task* next();
        void reset();
};
#endif // ITERATOR_H