//
// Created by banko on 2022. 10. 01..
//

#ifndef DYNAMICSTACK_DYNAMICSTACK_H
#define DYNAMICSTACK_DYNAMICSTACK_H
#include "exceptions.h"
#include <string>

using namespace std;

template <typename T>
class DynamicStack {
    struct Node{
        T value;
        Node *next;

        Node(const T& value_): value(value_), next(nullptr){};

    };

    Node *head;

public:
    DynamicStack();
    ~DynamicStack();
    void push(T new_item);
    T pop();
    T top() const;
    bool isEmpty() const;
    void print();
};

template <typename T>
DynamicStack<T>::DynamicStack() {
    head = nullptr;
}

template <typename T>
DynamicStack<T>::~DynamicStack() {
    while(!isEmpty()){
        pop();
    }
}

template <typename T>
bool DynamicStack<T>::isEmpty() const {
    return (head == nullptr);
}

template <typename T>
void DynamicStack<T>::push(T new_item) {
    Node* tmp = new Node(new_item);
    tmp->next = head;
    head = tmp;
}

template <typename T>
T DynamicStack<T>::pop() {
    if(isEmpty()){
        throw UnderFlowException();
    }
    T tmp = head->value;
    Node *p = head;
    head = head->next;
    delete p;

    return tmp;
}

template <typename T>
T DynamicStack<T>::top() const {
    if(isEmpty()){
        throw UnderFlowException();
    }
    return head->value;
}

template <typename T>
void DynamicStack<T>::print() {
    for (Node* n = head; n != nullptr; n = n->next){
        cout << n->value << " " << endl;
    }
}


#endif //DYNAMICSTACK_DYNAMICSTACK_H
