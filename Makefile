# A simple makefile for CSE 100 PA4

CC=g++
CXXFLAGS=-std=c++11
LDFLAGS=

# if passed "type=opt" at command-line, compile with "-O3" flag (otherwise use "-g" for debugging)

ifeq ($(type),opt)
    CPPFLAGS += -O3
    LDFLAGS += -O3
else
    CPPFLAGS += -g
    LDFLAGS += -g
endif

all: extension



# include what ever source code *.h files pathfinder relies on (these are merely the ones that were used in the solution)

pathfinder: ActorGraph.o pathfinder.o

actorconnections: ACGraph.o actorconnections.o

extension: FFGraph.o extension.o

# include what ever source code *.h files ActorGraph relies on (these are merely the ones that were used in the solution)

# Note: you do not have to include a *.cpp file if it aleady has a paired *.h file that is already included with class/method headers

ActorGraph.o: ActorGraph.h Casting.h ActorNode.h ActorEdge.h

ACGraph.o: ACGraph.h Casting.h ACNode.h

FFGraph.o: FFGraph.h FFNode.h

Casting.o: Casting.h
#UnionFind.hpp Movie.h ActorNode.h ActorEdge.h ActorGraph.h

ActorNode.o: ActorNode.h

ACNode.o: ACNode.h

FFNode.o: FFNode.h

clean:
	rm -f pathfinder *.o core*

