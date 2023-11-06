#include <iostream>
#include <thread>
#include <chrono>
//#include <cstdlib>  // For system function
//#include <fstream>  // Include this for std::ofstream
#include "label.hpp"
#include "queue.hpp"
#include "stack.hpp"
#include "van.hpp"


// the two include above need to be un commented if the result needs to be saved in the result.txt

#define N1 3500
#define N2 73  // Define the value of N2

// Function to distribute labels into stacks in steps of 73 labels -> the central station will distribute 73 packeges at a time.
void distributeLabels(Queue<Label>& initial, Stack<Label>& stackSE, Stack<Label>& stackSW, Stack<Label>& stackNE, Stack<Label>& stackNW) {
    for (int i = 0; i < N2 && !initial.empty(); ++i) {
        Label label = initial.dequeue();
        std::string packageID = label.getPackageID();
        std::string zoneCode = packageID.substr(packageID.size() - 2);

        // Determine the zone and push the label onto the appropriate stack
        if (zoneCode == "SE") {
            stackSE.push(label);
        } else if (zoneCode == "SW") {
            stackSW.push(label);
        } else if (zoneCode == "NE") {
            stackNE.push(label);
        } else if (zoneCode == "NW") {
            stackNW.push(label);
        }
        // Add conditions for other zones (SW, NE, NW) if needed
    }
}



int main() {
    
    // Redirect the output to a file
    //std::ofstream outputFile("result.txt");

    // Save the current state of the std::cout buffer
    //std::streambuf* coutBuffer = std::cout.rdbuf();

    // Redirect the output to the file
    //std::cout.rdbuf(outputFile.rdbuf());
    
    
    //un commnet the above comment to save the result in the file.txt
    
    
    // Create the initial queue with 3500 instances of Label
    Queue<Label> initial;
    for (int i = 0; i < N1; ++i) {
        initial.enqueue(Label()); // central station now has 3500 labels.
    }

    // Create separate stacks for each zone - Hubs 
    Stack<Label> stackSE;
    Stack<Label> stackSW;
    Stack<Label> stackNE;
    Stack<Label> stackNW;
    
    // Create Vans with identifiers -> as this is start up so 1 van for each Zone, to escale this more van instances can be created and be in use. 
    Van vanNE1("VanNE1");
    Van vanNW1("VanNW1");
    Van vanSE1("VanSE1");
    Van vanSW1("VanSW1");
    
    // taking the count of how many trips each van will complete by the end of the simulation. 
    int vanNE1Trips = 0;
    int vanNW1Trips = 0;
    int vanSE1Trips = 0;
    int vanSW1Trips = 0;
    
    // simulation round count. 
    int mainCount = 0;
    
    
    // Queues are each zone that will keep a track of what packages have been delivered to what zone. 
    Queue<Label> deliveredQueueSWCopy;
    Queue<Label> deliveredQueueNECopy;
    Queue<Label> deliveredQueueNWCopy;
    Queue<Label> deliveredQueueSECopy;
    
    // this is in use for the for the user to decide to continue with the program or not. 
    bool continueSimulation = true;

    // Distribute labels into stacks in steps of 73 labels as we know the numbers of distribution we know there are 48 rounds but if you didnt know just use mod or estimation. 
    while (continueSimulation && mainCount < 48) {
        // Wait for Enter key press
        std::cout << "Press Enter to continue to the next round...";
        while (true) {
            char input = std::cin.get();
            if (input == '\n') {
                break;
            }
        }
        
        
        // everytime increate the counter for the numbers by 1. 
        mainCount = mainCount + 1;
        distributeLabels(initial, stackSE, stackSW, stackNE, stackNW); // distribution of 73 packets 
        std::cout << "\nFinal State:" << std::endl;
        std::cout <<  "The Central Station Queue: " << initial.size() << std::endl;
        std::cout << "-----------------------------" << std::endl;
        std::cout << "Simulation round: " << mainCount << std::endl;
        std::cout << "-----------------------------" << std::endl;
        size_t size1 = stackSE.size(); //show after distribution how many of those 73 packets are in SE zones and so on. 
        std::cout << "size of the Stack SE" << size1 << std::endl;
    
        size_t size2 = stackSW.size();
        std::cout << "size of the Stack SW" << size2 << std::endl;
    
        size_t size3 = stackNE.size();
        std::cout << "size of the Stack NE" << size3 << std::endl;
    
        size_t size4 = stackNW.size();
        std::cout << "size of the Stack NW" << size4 << std::endl;
        // Load the vans with stacks
        
        vanSE1.loadVan(stackSE);
        std::cout << "van SE1 is loading..." << std::endl;
        
        vanNW1.loadVan(stackNW);
        std::cout << "van NW1 is loading..." << std::endl;
        
        vanNE1.loadVan(stackNE);
        std::cout << "van NE1 is loading..." << std::endl;
       
        vanSW1.loadVan(stackSW);
        std::cout << "van SW1 is loading..." << std::endl;
        
        // after that we load the vans as can be seen. 
        // if the van is full then it needs to delivers so 
        
    
        if (vanNE1.isFull()) {
            vanNE1Trips = vanNE1Trips + 1; // if full so increment the number of trips for the van. 
            std::cout << "Van NE1 is leaving..." << std::endl;
            vanNE1.leave();
            std::cout << "Van NE1 is deliverying..." << std::endl;
            vanNE1.deliver();
            std::cout << "Van NE1 is emptying the packets..." << std::endl;
            vanNE1.emptyVan();
            std::cout << "Van NE1 is returning back..." << std::endl;
            vanNE1.returnToStation();
            // this doest the simulation function as seen the van class. 
        } 
            
        if (vanNW1.isFull()) {
            vanNW1Trips = vanNW1Trips + 1;
            std::cout << "Van NW1 is leaving..." << std::endl;
            vanNW1.leave();
            std::cout << "Van Nw1 is deliverying..." << std::endl;
            vanNW1.deliver();
            std::cout << "Van NW1 is emptying..." << std::endl;
            vanNW1.emptyVan();
            std::cout << "Van NW1 is returning back..." << std::endl;
            vanNW1.returnToStation();
        }  
        if (vanSE1.isFull()) {
            vanSE1Trips = vanSE1Trips + 1;
            std::cout << "Van SE1 is leaving..." << std::endl;
            vanSE1.leave();
            std::cout << "Van SE1 is deliverying..." << std::endl;
            vanSE1.deliver();
            std::cout << "Van SE1 is emtying..." << std::endl;
            vanSE1.emptyVan();
            std::cout << "Van SE1 is returning back..." << std::endl;
            vanSE1.returnToStation();
        }  
        if (vanSW1.isFull()) {
            vanSW1Trips = vanSW1Trips + 1;
            std::cout << "Van SW1 is leaving..." << std::endl;
            vanSW1.leave();
            std::cout << "Van SW1 is deliverying..." << std::endl;
            vanSW1.deliver();
            std::cout << "Van SW1 is emptying..." << std::endl;
            vanSW1.emptyVan();
            std::cout << "Van SW1 is returning back..." << std::endl;
            vanSW1.returnToStation();
        }
                
        
        std::cout << "\nFinal State:" << std::endl;
        std::cout <<  "The Central Station Queue: " << initial.size() << std::endl;
        std::cout << "-----------------------------" << std::endl;
        std::cout << "Simulation round: " << mainCount << std::endl;
        std::cout << "-----------------------------" << std::endl;
        std::cout << "vanNE1 Trips: " << vanNE1Trips << std::endl;
        std::cout << "vanNW1 Trips: " << vanNW1Trips << std::endl;
        std::cout << "vanSE1 Trips: " << vanSE1Trips << std::endl;
        std::cout << "vanSW1 Trips: " << vanSW1Trips << std::endl;
        std::cout << "-----------------------------" << std::endl;
        std::cout << "-----------------------------" << std::endl;
        // Labels delivered to  NE
        
        // now that the van has delivered lets see what has been devilred using the delivered queue
        std::cout << "Labels delivered to NE\n" << std::endl;
        Queue<Label>& deliveredQueueNE = vanNE1.getDeliveredQueue();
        //create copy
        
        // present the copy 
        // in the function below We first created a counter to see the number of packages then enqueue them into a final queue and show the result too. 
        int t1 = 0;
        while (!deliveredQueueNE.empty()) {
            t1 += 1;
            Label label = deliveredQueueNE.dequeue(); // Dequeue a label from the original queue
            std::cout << t1 <<"|| " << label.getDestination() << ", ||  " << label.getPackageID() << "||  " << label.getClientID() << std::endl;
            deliveredQueueNECopy.enqueue(label);
            }
        std::cout << "-----------------------------" << std::endl;
        std::cout << "-----------------------------" << std::endl;    
        // Labels delivered to NW
        std::cout << "Labels delivered to NW\n" << std::endl;
        Queue<Label>& deliveredQueueNW = vanNW1.getDeliveredQueue();
        //create copy
        
        // present the copy 
        int t2 = 0;
        while (!deliveredQueueNW.empty()) {
            t2 += 1;
            Label label = deliveredQueueNW.dequeue(); // Dequeue a label from the original queue
            std::cout << t2 <<"|| " << label.getDestination() << ", ||  " << label.getPackageID() << "||  " << label.getClientID() << std::endl;
            deliveredQueueNWCopy.enqueue(label);
            }
        std::cout << "-----------------------------" << std::endl;
        std::cout << "-----------------------------" << std::endl;
        // Labels delivered to SE
        std::cout << "Labels delivered to SE\n" << std::endl;
        Queue<Label>& deliveredQueueSE = vanSE1.getDeliveredQueue();
        //create copy
       
        // present the copy 
        int t3 = 0;
        while (!deliveredQueueSE.empty()) {
            t3 += 1; 
            Label label = deliveredQueueSE.dequeue(); // Dequeue a label from the original queue
            std::cout << t3 <<"|| " << label.getDestination() << ", ||  " << label.getPackageID() << "||  " << label.getClientID() << std::endl;
            deliveredQueueSECopy.enqueue(label);
            }
        std::cout << "-----------------------------" << std::endl;
        std::cout << "-----------------------------" << std::endl;
        // Labels delivered to SW
        std::cout << "Labels delivered to SW\n" << std::endl;
        Queue<Label>& deliveredQueueSW = vanSW1.getDeliveredQueue();
        //create copy
        int t4 = 0;
        // present the copy 
        while (!deliveredQueueSW.empty()) {
            t4 += 1;
            Label label = deliveredQueueSW.dequeue(); // Dequeue a label from the original queue
            std::cout << t4 <<"|| " << label.getDestination() << ", ||  " << label.getPackageID() << "||  " << label.getClientID() << std::endl;
            deliveredQueueSWCopy.enqueue(label);
            }
    //here we are creating the choice for the user to continue or dont also we are handling all the errors of wrong input.         
    char choice;
    while (true) {
        std::cout << "\nDo you want to continue the simulation (y/n)? ";
        std::cin >> choice;
        if (choice == 'y' || choice == 'Y' || choice == 'n' || choice == 'N') {
            break;
        } else {
            std::cout << "Invalid input. Please enter 'y' or 'n'.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    continueSimulation = (choice == 'y' || choice == 'Y');
    
    }
    
    // after the intial queue is empty we have some packages still left in the Hubs Stacks so time to do the last delivery 
    size_t size1 = stackSE.size();
    std::cout << "size of the Stack SE" << size1 << std::endl;
    
    size_t size2 = stackSW.size();
    std::cout << "size of the Stack SW" << size2 << std::endl;
    
    size_t size3 = stackNE.size();
    std::cout << "size of the Stack NE" << size3 << std::endl;
    
    size_t size4 = stackNW.size();
    std::cout << "size of the Stack NW" << size4 << std::endl;
    
    
    // using above we have seen what has left in each stack. and if the stacks are not empty load them into the van. 
    if (!stackSE.empty()){
        vanSE1.loadVan(stackSE);
        }
    
    std::cout << "van SE1 is loading..." << std::endl;
    
    if (!stackNW.empty()){
        vanNW1.loadVan(stackNW);
        }
    std::cout << "van NW1 is loading..." << std::endl;
    
    if (!stackNE.empty()){
        vanNE1.loadVan(stackNE);
    }
    std::cout << "van NE1 is loading..." << std::endl;
    
    if (!stackSW.empty()){
        vanSW1.loadVan(stackSW);
    }
    std::cout << "van SW1 is loading..." << std::endl;
    
    // now deliver the remaning packegaes. 
    vanNE1Trips = vanNE1Trips + 1;
    std::cout << "Van NE1 is leaving..." << std::endl;
    vanNE1.leaveLast(); // allows the van to leave even tho its not full. 
    std::cout << "Van NE1 is deliverying..." << std::endl;
    vanNE1.deliver();
    std::cout << "Van NE1 is emptying the packets..." << std::endl;
    vanNE1.emptyVan();
    std::cout << "Van NE1 is returning back..." << std::endl;
    vanNE1.returnToStation();
    
    vanNW1Trips = vanNW1Trips + 1;
    std::cout << "Van NW1 is leaving..." << std::endl;
    vanNW1.leaveLast();
    std::cout << "Van Nw1 is deliverying..." << std::endl;
    vanNW1.deliver();
    std::cout << "Van NW1 is emptying..." << std::endl;
    vanNW1.emptyVan();
    std::cout << "Van NW1 is returning back..." << std::endl;
    vanNW1.returnToStation();
    
    vanSE1Trips = vanSE1Trips + 1;
    std::cout << "Van SE1 is leaving..." << std::endl;
    vanSE1.leaveLast();
    std::cout << "Van SE1 is deliverying..." << std::endl;
    vanSE1.deliver();
    std::cout << "Van SE1 is emtying..." << std::endl;
    vanSE1.emptyVan();
    std::cout << "Van SE1 is returning back..." << std::endl;
    vanSE1.returnToStation();
    
    vanSW1Trips = vanSW1Trips + 1;
    std::cout << "Van SW1 is leaving..." << std::endl;
    vanSW1.leaveLast();
    std::cout << "Van SW1 is deliverying..." << std::endl;
    vanSW1.deliver();
    std::cout << "Van SW1 is emptying..." << std::endl;
    vanSW1.emptyVan();
    std::cout << "Van SW1 is returning back..." << std::endl;
    vanSW1.returnToStation();
    
    std::cout << "\nFinal State:" << std::endl;
    std::cout <<  "The Central Station Queue: " << initial.size() << std::endl;
    std::cout << "-----------------------------" << std::endl;
    std::cout << "Simulation round: " << mainCount << std::endl;
    std::cout << "-----------------------------" << std::endl;
    std::cout << "vanNE1 Trips: " << vanNE1Trips << std::endl;
    std::cout << "vanNW1 Trips: " << vanNW1Trips << std::endl;
    std::cout << "vanSE1 Trips: " << vanSE1Trips << std::endl;
    std::cout << "vanSW1 Trips: " << vanSW1Trips << std::endl;
    std::cout << "-----------------------------" << std::endl;
    std::cout << "-----------------------------" << std::endl;
        // Labels delivered to  NE
    std::cout << "Labels delivered to NE\n" << std::endl;
    Queue<Label>& deliveredQueueNE = vanNE1.getDeliveredQueue();
        //create copy
    
        // present the copy 
    while (!deliveredQueueNE.empty()) {
        Label label = deliveredQueueNE.dequeue(); // Dequeue a label from the original queue
        std::cout << "|| " << label.getDestination() << ", ||  " << label.getPackageID() << "||  " << label.getClientID() << std::endl;
        deliveredQueueNECopy.enqueue(label);
        }
    std::cout << "-----------------------------" << std::endl;
    std::cout << "-----------------------------" << std::endl;    
        // Labels delivered to NW
    std::cout << "Labels delivered to NW\n" << std::endl;
    Queue<Label>& deliveredQueueNW = vanNW1.getDeliveredQueue();
        //create copy
    
        // present the copy 
    while (!deliveredQueueNW.empty()) {
        Label label = deliveredQueueNW.dequeue(); // Dequeue a label from the original queue
        std::cout << "|| " << label.getDestination() << ", ||  " << label.getPackageID() << "||  " << label.getClientID() << std::endl;
        deliveredQueueNWCopy.enqueue(label);
        }
    std::cout << "-----------------------------" << std::endl;
    std::cout << "-----------------------------" << std::endl;
        // Labels delivered to SE
    std::cout << "Labels delivered to SE\n" << std::endl;
    Queue<Label>& deliveredQueueSE = vanSE1.getDeliveredQueue();
        //create copy
    
        // present the copy 
    while (!deliveredQueueSE.empty()) {
        Label label = deliveredQueueSE.dequeue(); // Dequeue a label from the original queue
        std::cout << "|| " << label.getDestination() << ", ||  " << label.getPackageID() << "||  " << label.getClientID() << std::endl;
        deliveredQueueSECopy.enqueue(label);
        }
    std::cout << "-----------------------------" << std::endl;
    std::cout << "-----------------------------" << std::endl;
        // Labels delivered to SW
    std::cout << "Labels delivered to SW\n" << std::endl;
    Queue<Label>& deliveredQueueSW = vanSW1.getDeliveredQueue();
        //create copy
    
        // present the copy 
    while (!deliveredQueueSW.empty()) {
        Label label = deliveredQueueSW.dequeue(); // Dequeue a label from the original queue
        std::cout << "|| " << label.getDestination() << ", ||  " << label.getPackageID() << "||  " << label.getClientID() << std::endl;
        deliveredQueueSWCopy.enqueue(label);
        }
     
    // the above was exactly like the loop part and now its time to show the full result -> thats why we copied the queue everytime we try to show it so the complete result has been gaurded in the COPY queue. 
    std::cout << "-----------------------------" << std::endl;
    std::cout << "-----------------------------" << std::endl;
    std::cout << "-----------------------------" << std::endl;
    std::cout << "FINAL DELIVERED RESULT" << std::endl;
    std::cout << "-----------------------------" << std::endl;
    std::cout << "-----------------------------" << std::endl;
    std::cout << "Labels delivered to NE\n" << std::endl;
    // create a counter to see how many packages are in the each Zones at the end. and showing them. 
    int c1 = 0;
    while (!deliveredQueueNECopy.empty()) {
        c1 += 1;
        Label label = deliveredQueueNECopy.dequeue();
        std::cout << c1 << "|| " << label.getDestination() << ", ||  " << label.getPackageID() << "||  " << label.getClientID() << std::endl;
        }
    std::cout << "-----------------------------" << std::endl;
    std::cout << "-----------------------------" << std::endl;
    std::cout << "Labels delivered to NW\n" << std::endl;
    int c2 = 0;
    while (!deliveredQueueNWCopy.empty()){
        c2 += 1;
        Label label = deliveredQueueNWCopy.dequeue();
        std::cout << c2 <<"|| " << label.getDestination() << ", ||  " << label.getPackageID() << "||  " << label.getClientID() << std::endl;
        }
    std::cout << "-----------------------------" << std::endl;
    std::cout << "-----------------------------" << std::endl;
    std::cout << "Labels delivered to SE\n" << std::endl;
    int c3 = 0;
    while (!deliveredQueueSECopy.empty()){
        c3 += 1;
        Label label = deliveredQueueSECopy.dequeue();
        std::cout << c3 <<"|| " << label.getDestination() << ", ||  " << label.getPackageID() << "||  " << label.getClientID() << std::endl;
        }
    
    std::cout << "-----------------------------" << std::endl;
    std::cout << "-----------------------------" << std::endl;
    std::cout << "Labels delivered to SW\n" << std::endl;
    int c4 = 0;
    while (!deliveredQueueSWCopy.empty()) {
        c4 += 1;
        Label label = deliveredQueueSWCopy.dequeue();
        std::cout << c4 <<"|| " << label.getDestination() << ", ||  " << label.getPackageID() << "||  " << label.getClientID() << std::endl;
        }
    
    
    // the comment below are neeeded to be uncommneted if the result is desired to be saved in the result.txt
    // Restore the std::cout buffer
    //std::cout.rdbuf(coutBuffer);

    // Close the output file
    //outputFile.close();
    return 0;
}
// Queue<Label>& deliveredQueue = van.getDeliveredQueue(); for the prints


// lets run the simulation. 