#include "TaskIterator.h"

TaskIterator::TaskIterator(Node<Task>* head) : current(head), start(head) {}

bool TaskIterator::hasNext() const {
    return current != nullptr;
}

Task* TaskIterator::next() {
    if (!hasNext()) return nullptr;
    Task* result = &(current->data);
    current = current->next;
    return result;
}

void TaskIterator::reset() {
    current = start;
}
