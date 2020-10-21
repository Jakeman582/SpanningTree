#ifndef BRIDGE_HPP
#define BRIDGE_HPP

#include <string>
#include <unordered_map>

using namespace std;

struct Port {
    string currentRoot; // What this port thinks is the root node
    int distance;       // Distance to the root node
    string id;          // The name of this port (the LAN)
    bool open;          // Is this port open?
};

class Bridge {

    public:
        Bridge(string newId);
        void addPort(string newPort);
        void reconfigure(string port, string root, int distance, string receiveId);
        void printBridge();

        string id;                              // This bridge's name
        string rootNode;                        // What this bridge thinks is the root node
        int distanceToRoot;                     // Number of hops from this bridge to the root bridge
        string receiveNode;                     // Which node told this bridge the root node
        string designatedPort;                  // The port used to forward messages to root
        unordered_map<string, Port> ports;      // The set of ports for this bridge

};

#endif
