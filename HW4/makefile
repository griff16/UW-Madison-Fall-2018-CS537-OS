CC = gcc
WARNING_FLAGS = -g -Wall -Wextra
EXE = simple_testcase1

SCAN_BUILD_DIR = scan-build-out

all: simple_testcase1.o 537malloc.o AVLTree.o tuple.o
	$(CC) -o $(EXE) simple_testcase1.o 537malloc.o AVLTree.o tuple.o

simple_testcase1.o: simple_testcase1.c 537malloc.h
	$(CC) $(WARNING_FLAGS) -c simple_testcase1.c

537malloc.o: 537malloc.c AVLTree.h tuple.h
	$(CC) $(WARNING_FLAGS)  -c 537malloc.c

AVLTree.o: AVLTree.c tuple.h
	$(CC) $(WARNING_FLAGS) -c AVLTree.c

tuple.o: tuple.c
	$(CC) $(WARNING_FLAGS) -c tuple.c

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
