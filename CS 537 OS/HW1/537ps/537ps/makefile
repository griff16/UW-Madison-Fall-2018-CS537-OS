# CS 537 Fall 2018 
# Program Assignment 1
# Student 1: Xiao Zhang     
# Student 2: Yanting Liang   

CC = gcc
WARNING_FLAGS = -Wall -Wextra
EXE = 537ps
SCAN_BUILD_DIR = scan-build-out

all: main.o func_p.o func_state.o func_stime.o func_U.o func_v.o func_c.o func_all.o func_print.o isnumber.o cmpstring.o
	$(CC) -o $(EXE) main.o func_p.o func_state.o func_stime.o func_U.o func_v.o func_c.o func_all.o func_print.o isnumber.o cmpstring.o

main.o: main.c func_all.h func_print.h isnumber.h
	$(CC) $(WARNING_FLAGS) -c main.c

func_p.o: func_p.c func_p.h
	$(CC) $(WARNING_FLAGS) -c func_p.c

func_state.o: func_state.c func_state.h
	$(CC) $(WARNING_FLAGS) -c func_state.c

func_stime.o: func_stime.c func_stime.h
	$(CC) $(WARNING_FLAGS) -c func_stime.c

func_U.o: func_U.c func_U.h
	$(CC) $(WARNING_FLAGS) -c func_U.c

func_v.o: func_v.c func_v.h
	$(CC) $(WARNING_FLAGS) -c func_v.c

func_c.o: func_c.c func_c.h
	$(CC) $(WARNING_FLAGS) -c func_c.c

func_all.o: func_all.c func_all.h func_p.h func_print.h cmpstring.h
	$(CC) $(WARNING_FLAGS) -c func_all.c

func_print.o: func_print.c func_print.h func_p.h func_state.h func_U.h func_state.h func_v.h func_c.h
	$(CC) $(WARNING_FLAGS) -c func_print.c

isnumber.o: isnumber.c isnumber.h
	$(CC) $(WARNING_FLAGS) -c isnumber.c

cmpstring.o: cmpstring.c cmpstring.h
	$(CC) $(WARNING_FLAGS) -c cmpstring.c

clean:
	rm $(EXE) *.o
	rm -rf $(SCAN_BUILD_DIR)

# Run the Clang Static Analyzer
scan-build: clean
	scan-build -o $(SCAN_BUILD_DIR) make

# View the one scan available using firefox
scan-view: scan-build
	firefox -new-window $(SCAN_BUILD_DIR)/*/index.html 
