#include <iostream>
#include "Bridge.hpp"

using namespace std;

Bridge::Bridge(string newId) {

    id = newId;
    rootNode = newId;
    distanceToRoot = 0;
    designatedPort = "";

}

void Bridge::addPort(string newPort) {

    // Add each port specified by the input file given to the program
    struct Port portConfiguration = {id, distanceToRoot, id, true};
    ports.insert({newPort, portConfiguration});

}

void Bridge::reconfigure(string port, string root, int distance, string receiveId) {

    // Determine if this bridge is the designated bridge for the specified LAN
    unordered_map<string, Port>::iterator matchingPort = ports.find(port);

    // Make sure the port is on this bridge
    if(ports.find(matchingPort->first) == ports.end()) {
        return;
    }

    // Check if the new message is better for this port
    if(matchingPort->second.currentRoot > root) {   // Found a smaller bridge id for a root node
        matchingPort->second.currentRoot = root;
        matchingPort->second.distance = distance + 1;
        matchingPort->second.id = id;
    } else if(matchingPort->second.currentRoot == root && matchingPort->second.distance > distance) {   // Found a shorter distance
        matchingPort->second.currentRoot = root;
        matchingPort->second.distance = distance + 1;
        matchingPort->second.id = id;
    } else if(matchingPort->second.currentRoot == root && matchingPort->second.distance == distance && matchingPort->second.id > id) {  // Found a neighbor node with a  smaller id
        matchingPort->second.currentRoot = root;
        matchingPort->second.distance = distance + 1;
        matchingPort->second.id = id;
    } else {
        // The message was not better, so ignore it
        return;
    }

    // Check if the message is better than the node's message
    if(rootNode > root) {   // Found a smaller root node
        rootNode = root;
        distanceToRoot = distance + 1;
        receiveNode = receiveId;
        designatedPort = port;
    } else if(rootNode == root && distanceToRoot > distance) {  // Found a shorter distance to the root node
        rootNode = root;
        distanceToRoot = distance + 1;
        receiveNode = receiveId;
        designatedPort = port;
    }

    // Check each port to see if it should now be closed
    unordered_map<string, Port>::iterator currentPort = ports.begin();
    while(currentPort != ports.end()) {
        if(currentPort->first != designatedPort && currentPort->second.currentRoot != id) {
            // Close each port that received a message from a non-root node
            currentPort->second.open = false;
        }
        currentPort++;
    }

}

void Bridge::printBridge() {

    // Print the bridge configuration
    cout << "Bridge " << id << ": best configuration <" << rootNode << ", " << distanceToRoot << ">, from " << receiveNode;
    if(id != rootNode) {
        cout << " via " << designatedPort;
    }
    cout << endl;

    // Print the configuration of every node
    unordered_map<string, Port>::iterator currentPort = ports.begin();
    while(currentPort != ports.end()) {
        Port temp = currentPort->second;
        cout << "    port " << currentPort->first << ":  <" << temp.currentRoot << ", " << temp.distance << ", " << temp.id << ">  ";
        if(temp.open) {
            cout << "open";
        } else {
            cout << "closed";
        }
        cout << endl;
        currentPort++;
    }
    cout << endl;
}
