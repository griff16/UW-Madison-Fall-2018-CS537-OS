CC = gcc
WARNING_FLAGS = -g -Wall -Wextra
EXE = 537make

SCAN_BUILD_DIR = scan-build-out

all: main.o buildGraph.o execution.o queue.o graph.o graphNode.o
	$(CC) -o $(EXE) main.o buildGraph.o execution.o queue.o graph.o graphNode.o  

main.o: main.c buildGraph.h execution.h
	$(CC) $(WARNING_FLAGS)  -c main.c

buildGraph.o: buildGraph.c graph.h graphNode.h
	$(CC) $(WARNING_FLAGS) -c buildGraph.c 

execution.o: execution.c graph.h queue.h
	$(CC) $(WARNING_FLAGS) -c execution.c

queue.o: queue.c graphNode.h 
	$(CC) $(WARNING_FLAGS) -c queue.c

graph.o: graph.c graphNode.h
	$(CC) $(WARNING_FLAGS) -c graph.c

graphNode.o: graphNode.c
	$(CC) $(WARNING_FLAGS) -c graphNode.c


clean:
	rm -f $(EXE) *.o
	rm -rf $(SCAN_BUILD_DIR)

#
# Run the Clang Static Analyzer
#
scan-build: clean
	scan-build -o $(SCAN_BUILD_DIR) make

#
# View the one scan available using firefox
#
scan-view: scan-build
	firefox -new-window $(SCAN_BUILD_DIR)/*/index.html 
