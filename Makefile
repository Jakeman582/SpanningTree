SOURCES = spanningtree.cpp Bridge.cpp Bridge.hpp

all: $(SOURCES)
	g++ $(SOURCES) -o spanningtree
