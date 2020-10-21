## Spanning Tree Protocol Simulation

A simulation of the Spanning Tree Protocol used by switches and bridges to construct a loop-free model of the given network.  

**Basic Description**  

First, my program attempts to open a network config file and create all of the necessary  
bridges and their associated ports. It then goes through each of the bridges listed in the  
argument vector to reconfigure each of the ports on each of the neighbor bridges. Finally,  
the configuration of each bridge is printed.  

Spannign tree protocol relies on messages being sent between neighbor nodes containing three pieces of information: the ID of the root node, the number of hops from this node to the root node, and the designated node.  

**Network specification file**  

This file serves as input to the program, and contains a description of the extended LAN.  
Each line represents a Bridge, named with a number. If there are n bridges in the extended LAN, then there will be n lines in the file.  
Each bridge is connected to a set of LANs, which are denoted by capital letters.  
  
Here is an example network config file:  

1 D E F G H  
2 C E  
3 A C  
4 H I J  
5 A B D  
6 G I  
7 B F K  

Here, Bridge 1 has five ports, connected to LANs D, E, F, G, and H. Similarly, Bridge 5 is connected to LANs A, B, and D.  

**Specifying which nodes send messages**  

As this is a simulation, we needed a way to coax each bridge to send messages. We do this by specifying a list of numbers to the spanningtree program.  
  
This list of numbers is specified after supplying the network file to the program (arguments 2, 3, 4, ...).  
Each number represents a bridge, and the order of the numbers listed is the order inwhich bridges will be selected to send messages.  
  
For example, if we run the command *linux> ./spanningtree network.txt 1 2 3 2 1 3*, then this is the sequence of messages that will be implemented:  
1.) From Bridge 1 to it's neighbors  
2.) From Bridge 2 to it's neighbors  
3.) From Bridge 3 to it's neighbors  
4.) From Bridge 2 to it's neighbors  
5.) From Bridge 1 to it's neighbors  
6.) From Bridge 3 to it's neighbors  
  
**Example usage:**  
  
linux> ./spanningtree network.txt 1 2 3 4 5  
Bridge 7: best configuration <1, 1>, from 1 via F  
    port B:  <1, 2, 7>  closed  
    port K:  <7, 0, 7>  open  
    port F:  <1, 1, 7>  open  
  
Bridge 2: best configuration <1, 1>, from 1 via E  
    port E:  <1, 1, 2>  open  
    port C:  <1, 3, 2>  closed  
  
Bridge 1: best configuration <1, 0>, from   
    port H:  <1, 0, 1>  open  
    port G:  <1, 0, 1>  open  
    port F:  <1, 0, 1>  open  
    port D:  <1, 0, 1>  open  
    port E:  <1, 0, 1>  open  
  
Bridge 5: best configuration <1, 1>, from 1 via D  
    port D:  <1, 1, 5>  open  
    port A:  <1, 3, 5>  closed  
    port B:  <5, 0, 5>  open  
  
Bridge 3: best configuration <1, 2>, from 2 via C  
    port C:  <1, 2, 3>  open  
    port A:  <3, 0, 3>  open  
  
Bridge 4: best configuration <1, 1>, from 1 via H  
    port J:  <4, 0, 4>  open  
    port H:  <1, 1, 4>  open  
    port I:  <4, 0, 4>  open  
  
Bridge 6: best configuration <1, 1>, from 1 via G  
    port I:  <1, 2, 6>  closed  
    port G:  <1, 1, 6>  open  
