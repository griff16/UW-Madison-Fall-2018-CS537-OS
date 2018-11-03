CC = gcc
WARNING_FLAGS = -Wall -Wextra
PTHREAD_FLAG = -lpthread
EXE = prodcomm

SCAN_BUILD_DIR = scan-build-out

all: prodcomm.o Reader.o Munch1.o Munch2.o Writer.o Queue.o
	$(CC) -o $(EXE) prodcomm.o Reader.o Munch1.o Munch2.o Writer.o Queue.o $(PTHREAD_FLAG)

prodcomm.o: prodcomm.c Reader.h Munch1.h Munch2.h Writer.h Queue.h struct.h
	$(CC) $(WARNING_FLAGS)  -c prodcomm.c $(PTHREAD_FLAG)

Reader.o: Reader.c Reader.h Queue.h
	$(CC) $(WARNING_FLAGS) -c Reader.c $(PTHREAD_FLAG) 

Munch1.o: Munch1.c Munch1.h Queue.h struct.h
	$(CC) $(WARNING_FLAGS) -c Munch1.c $(PTHREAD_FLAG)

Munch2.o: Munch2.c Munch2.h Queue.h struct.h
		$(CC) $(WARNING_FLAGS) -c Munch2.c  $(PTHREAD_FLAG)

Writer.o: Writer.c Writer.h Queue.h
	$(CC) $(WARNING_FLAGS) -c Writer.c $(PTHREAD_FLAG)

Queue.o: Queue.c Queue.h
	$(CC) $(WARNING_FLAGS) -c Queue.c $(PTHREAD_FLAG)

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