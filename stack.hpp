#ifndef STACK_HPP
#define STACK_HPP

#include <vector>

template <typename T>
class Stack {
public:
    Stack();
    bool empty() const;
    size_t size() const;
    void push(const T& value);
    void pop();
    T& top();
    const T& top() const;

private:
    std::vector<T> elements;
};

template <typename T>
Stack<T>::Stack() {}

//check to see if the stack is empty
template <typename T>
bool Stack<T>::empty() const {
    return elements.empty();
}


// get the size of the stack 
template <typename T>
size_t Stack<T>::size() const {
    return elements.size();
}


// the push function thatrecieves the element and push to the top of the stack 
template <typename T>
void Stack<T>::push(const T& value) {
    elements.push_back(value);
}


// first check if the stack is not empty the pop the element
template <typename T>
void Stack<T>::pop() {
    if (empty()) {
        throw std::runtime_error("Stack is empty.");
    }
    elements.pop_back();
}


// this functions return the top of the stack like the front in the queue
template <typename T>
T& Stack<T>::top() {
    if (empty()) {
        throw std::runtime_error("Stack is empty.");
    }
    return elements.back();
}


// at first this might look the same but the second function returns const. 
template <typename T>
const T& Stack<T>::top() const {
    if (empty()) {
        throw std::runtime_error("Stack is empty.");
    }
    return elements.back();
}

#endif // STACK_HPP


// all decleration for the stack class 