// van.hpp
#ifndef VAN_HPP
#define VAN_HPP

#include "stack.hpp"
#include "queue.hpp"
#include "label.hpp"
#include <string>
#include <chrono>
#include <thread>

#define N3 24  // Define N3 as 24

class Van {
private:
    const std::string identifier;
    static const int MAX_CAPACITY = N3;
    
    Queue<Label> deliveredQueue; // Member variable to store delivered labels
    bool full;

public:

    Stack<Label> loadedStack;
    
    Van(const std::string& identifier);
    void loadVan(Stack<Label>& stack);
    void leave();
    void leaveLast();
    void deliver();
    void emptyVan();
    void returnToStation();
    bool isFull() const;
    void simulateDelivery(Stack<Label>& stack);
    void waitForSeconds(int seconds);
    
    // Public function to access deliveredQueue
   Queue<Label>& getDeliveredQueue() {
    return deliveredQueue;
    }   
};

#endif