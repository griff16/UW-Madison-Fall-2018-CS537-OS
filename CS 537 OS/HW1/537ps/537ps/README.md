# Project 1: 537ps

The assignment is to write a simple version of the ps command. Our version of ps, called 537ps be executed from a command line. It will read a variety of information about one or more running programs (processes) on the computer, and then display that information.

## Run the program

1. Compile multiple files, also generate object files and a final prog

```
make
```

2. Enter command line with flags

```
537ps -p 1234 -s -U -c
```

3. The prog runs our ps command, and displays the status letter (in this case, running), amount of user time, and the command line for process 1234. We might expect the output to look like:

```
1234: R utime=150 [myprog -x -y file1 myoption]
```
4. Delete all .o files and prog

```
make clean
```

## Features

* -p <pid>

    Display process information only for the process whose number is pid. If this option is not present then display information for all processes of the current user.
    
* -s

    Display the single-character state information about the process. This information is found in the stat file in process's directory, looking at the third ("state") field. Note that the information that you read from the stat file is a character string. This option defaults to be **false**, so if it is not present, do not display this information. -s- is valid but has no effect.

* -U

    Display the amount of user time consumed by this process. This information is found in the stat file in process's directory, looking at the "utime" field. This option defaults to be **true**, so if it is not present, then this information is displayed. -U- turns this option off.
* -S

    Display the amount of system time consumed so far by this process. This information is found in the stat file in process's directory, looking at the "stime" field. This option defaults to be **false**, so if it is not present, then this information is **not** displayed. -S- is valid but has no effect.
    
* -v

    Display the amount of virtual memory currently being used (in pages) by this program. This information is found in the statm file in process's directory, looking at first ("size") field. This option defaults to be **false**, so if it is not present, then this information is **not** displayed. -v- is valid but has no effect.
    
* -c

    Display the command-line that started this program. This information is found in the cmdline file in process's directory. Be careful on this one, because this file contains a list of null (zero byte) terminated strings. This option defaults to be **true**, so if it is not present, then this information is displayed. -c- turns this option off.

## Functions

* main ( )

    The main function is where to read in command line and goes through the command line input. It checks if inputs are valid or invalid and sets flags for each feature. It calls **func_print( )** to print out process information of given **pid** if it exits; otherwise, it calls **func_all( )** to print out all process of current user.
    
* func_p ( )

    This function tries to search the folder with the given **pid**. If the folder is found, we print out the **pid** and set the flag to **1**. If the flag is **0**, we print out error message.

* func_state ( )

    This function opens "/proc/$pid/stat" path, find the 3rd field which is the single-character state information about the process,  and display the state information about the process.

* func_stime ( )

    This function opens "/proc/$pid/stat" path, find the 15th field which stands for the amount of system time consumed so far by this process, and display the stime.

* func_U ( )

    This function opens "/proc/$pid/stat" path, find the 14th field which stands for the amount of user time consumed by this process, and display the utime.

* func_v ( )

    This function opens "/proc/$pid/statm" path and display the amount of virtual memory current being used by the corresponding program.
    
* func_c ( )

    This function opens "/proc/$pid/cmdline" path and display the command line stored in the cmdline file.
    
* func_all ( )

    This function prints out all process information for current user. It stores all pids of processes belonging to the current user to an array, and sorts all pids in the array in ascending order. Then it calls **func_p( )** and **func_print( )** to print out all process information.

* func_print ( )

    This function checks flags for each feature. If the flag for a feature is **1**, it will call the corresponding function for display output.

* isnumber ( )

    This function checks if an argument is a number. If it is a number, return **1**; otherwise return **0**.

* cmpstring ( )

    This function compares two strings and it is used for qsort. It sorts an array in ascending order.

