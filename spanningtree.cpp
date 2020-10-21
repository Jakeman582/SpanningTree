#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include "Bridge.hpp"

using namespace std;

int main(int argc, char** argv) {

    // Make sure the program is called correctly
    if(argc < 3) {
        cout << "Correct usage: spanningtree file_name bridge1 [bridge2, ...]" << endl;
        exit(0);
    }

    // Attempt to open the file and abort if unsuccessful
    ifstream inputFile;
    inputFile.open(argv[1]);
    if(inputFile.fail()) {
        cout << "Failed to open file " << argv[1] << endl;
        exit(0);
    }

    // At this point, we can start collecting information about our simple
    // network
    unordered_map<string, Bridge> bridges;

    // Each line describes a bridge and it's ports
    istringstream inputString;
    string configuration;
    string name;
    string port;
    int index = 0;
    while(getline(inputFile, configuration)) {
        inputString.clear();
        inputString.str(configuration);
        inputString >> name;
        bridges.insert({name, Bridge(name)});   // Name the bridge
        while(inputString >> port) {    // Get each of the bridge's ports
            bridges.find(name)->second.addPort(port);
        }
        index++;
    }

    inputFile.close();

    // Have each bridge send a message
    for(int index = 2; index < argc; index++) {
        Bridge sendingBridge = bridges.find(argv[index])->second;
        
        // For each open port on the bridge, send a message
        unordered_map<string, Port>::iterator port = sendingBridge.ports.begin();
        while(port != sendingBridge.ports.end()) {
            if(port->second.open) { // Send messages only on open ports
                string portName = port->first;
                string portId = port->second.id;

                // Send the message to each bridge with the same port
                unordered_map<string, Bridge>::iterator receivingBridge = bridges.begin();
                while(receivingBridge != bridges.end()) {
                    if(receivingBridge->second.id != sendingBridge.id) {
                        if(receivingBridge->second.ports.find(portName) != receivingBridge->second.ports.end()) {
                            receivingBridge->second.reconfigure(portName, sendingBridge.rootNode, sendingBridge.distanceToRoot, sendingBridge.id);
                        }
                    }
                    receivingBridge++;
                }
            }
            port++;
        }
    }

    // print each bridge config
    unordered_map<string, Bridge>::iterator bridge = bridges.begin();
    while(bridge != bridges.end()) {
        bridge->second.printBridge();
        bridge++;
    }

    return 0;

}
