## Spannign Tree Protocol Simulation

Example usage:

./spanningtree network.txt 1 2 3 4 5

In my program, I define a Bridge class and a Port struct.

First, my program attempts to open a network config file and create all of the necessary
bridges and their associated ports. It then goes through each of the bridges listed in the
argument vector to reconfigure each of the ports on each of the neighbor bridges. Finally,
the configuration of each bridge is printed.

One design decision made early on was to use unordered_map objects to hold bridges
and ports so they can be accessed and referenced quickly by way of string identifiers.
Another goal was honestly just to get practice using them in a project, since hash maps
tend to crop up a lot in many situations.