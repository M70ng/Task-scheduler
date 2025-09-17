/*
Tests Task class
*/

#include <iostream>
using namespace std;

#include "../src/Task.h"

int main() {
    Task t1("T1", "Test Task", 5, 20231010, "T0");
    t1.display();
    return 0;
};