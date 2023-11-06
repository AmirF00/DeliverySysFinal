#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>
#include <vector>

template <typename T>
class Queue {
public:
    Queue();
    bool empty() const;
    size_t size() const;
    void enqueue(const T& value);
    T dequeue();
    T front() const;

private:
    std::vector<T> data;
};

// Implementation of template class should be in the header file.
// The method definitions are included in the header file.

template <typename T>
Queue<T>::Queue() {}

template <typename T>
bool Queue<T>::empty() const {
    return data.empty();
}

template <typename T>
size_t Queue<T>::size() const {
    return data.size();
}

template <typename T>
void Queue<T>::enqueue(const T& value) {
    data.push_back(value);
}

template <typename T>
T Queue<T>::dequeue() {
    if (empty()) {
        throw std::runtime_error("Queue is empty.");
    }
    // check to see if the queue is not empty then we can continue with dequeuing. 
    T front = data.front();
    data.erase(data.begin());
    return front;
}

template <typename T>
T Queue<T>::front() const {
    if (empty()) {
        throw std::runtime_error("Queue is empty.");
    }
    return data.front();
}

// this is the quivalent of top for stacks. 

#endif // QUEUE_HPP


// in this class we declare all necessaries for the Queue