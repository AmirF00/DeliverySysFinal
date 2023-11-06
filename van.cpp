// van.cpp
#include "van.hpp"

Van::Van(const std::string& identifier) : identifier(identifier), full(false) {
    // Constructor implementation
}


// this function gets an stack as input and load the van considering the van has max capacity of 24. 
void Van::loadVan(Stack<Label>& stack) {
    while (!stack.empty() && loadedStack.size() < MAX_CAPACITY) {
        loadedStack.push(stack.top());
        stack.pop();
    }
    
    if (loadedStack.size() == MAX_CAPACITY) {
        full = true;
        
    }
}

// van leaves the times of the following functions can be adjusted. so if you want the process to look more like real time you can increase the time
void Van::leave() {
    while (!full) {
        // Keep loading labels until the van is full
        // warning for using decimal, it will be fine if used natural numbers. 
        waitForSeconds(0.1);
    }
}

void Van::leaveLast() {
    // this one doesnt have the while loop of not full allowing the van to leave with out being full 
        waitForSeconds(0.1);
}

void Van::deliver() {
    waitForSeconds(0.3); // Simulate delivery time
    emptyVan(); // take time to deliver and the empty the van 
}

void Van::emptyVan() {
    while (!loadedStack.empty()) {
        deliveredQueue.enqueue(loadedStack.top()); // equeue the result (stack.pop) into the delivered queue this funtion will empty the whole van till the van stack is empty. 
        loadedStack.pop();
    }
    full = false; // The van is now empty
}

void Van::returnToStation() {
    waitForSeconds(0.3); // Simulate return time
}


// check if the van is full. 
bool Van::isFull() const {
    return full;
}


// the following can be used to simulate the van - however We decided otherwise but its nice funtion to have in hand. 
void Van::simulateDelivery(Stack<Label>& stack) {
    loadVan(stack); // Load the van with the provided stack
    leave(); // Leave when the van is full
    deliver(); // Deliver labels
    returnToStation(); // Return to the station
}


// this is for the waiting or in other words for the simulating the delivery. 
void Van::waitForSeconds(int seconds) {
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}