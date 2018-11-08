#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h>
int main(int argc, char** argv){
    // target that is not a file and needs to be executed
	// char* string = node->target;

    char* target = argv[1];
    if(target[strlen(target) - 2] != '.') return 1; 
    
	time_t time_one, time_two;
	char* path_target = malloc((strlen(target) + 3) * sizeof(char));
	struct stat statbuff_one, statbuff_two;

	// getting the target last modified time 
	strcpy(path_target, "./");
	strcat(path_target, target);
	stat(path_target, &statbuff_one);  // double check this part
	time_one = statbuff_one.st_mtime;
    puts("dededdeded");
    printf("path1: %s\n", path_target);
    printf("time_one: %ld\n", time_one);

    stat("./experiment.c", &statbuff_two);
    time_two = statbuff_two.st_mtime;
    printf("path2: %s\n", "./experiment.c");
    printf("time_:two %ld\n", time_two);

    printf("difftime:%f\n",difftime(time_one, time_two));



	// getting the dependency files' last modified times and check if it is out of date
	// int i;
	// for(i = 0; i < graph->graph_size; i++){
	// 	if(graph->adj_matrix[index][i] == 1){  // found the dependent file
	// 		char* dependent = malloc((strlen(graph->graph_nodes[i]->target) + 3) * sizeof(char));
	// 		strcpy(dependent, "./");
	// 		strcat(dependent, graph->graph_nodes[i]->target);
	// 		if(stat(dependent, &statbuff_two) == -1){
	// 			printf("cannot open the path: %s", dependent);
	// 			exit(-1);
	// 		}
	// 		time_two = statbuff_two.st_mtime;
			
	// 		// compare two times 
	// 		if(difftime(time_one, time_two) <= 0) return 1;
	// 	}
	// }
    puts("return 0");
    return 0;
}
