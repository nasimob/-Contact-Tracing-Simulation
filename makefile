# All Targets
all: cTrace

# Tool invocations

cTrace: bin/Tree.o bin/main.o bin/Graph.o bin/Session.o bin/Agent.o
	g++ -o bin/cTrace bin/Tree.o bin/main.o bin/Session.o bin/Graph.o bin/Agent.o



# Depends on the source and header files

bin/Tree.o: src/Tree.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Tree.o src/Tree.cpp
bin/Agent.o: src/Agent.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Agent.o src/Agent.cpp
bin/Session.o: src/Session.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Session.o src/Session.cpp
bin/Graph.o: src/Graph.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Graph.o src/Graph.cpp
bin/main.o: src/main.cpp
		g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/main.o src/main.cpp

#Clean the build directory
clean:
	rm -f bin/*