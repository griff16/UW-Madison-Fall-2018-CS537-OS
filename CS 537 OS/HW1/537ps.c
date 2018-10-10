#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

/*
* Xiao Zhang
* Partner: Yanting Liang
*/

FILE* fp;
DIR* procf;
struct dirent *dp;
int i;  // for loop variable
char buffer[256] = "";
char temp[256];

void func_p(char* pid){
    int flag = 0;
    procf = opendir("/proc");
    while ((dp = readdir(procf)) != NULL){
        if(strcmp(dp -> d_name, pid) == 0){
            printf("%s: ",dp -> d_name);
            flag = 1;
            break;
        }
    }
    if (flag == 0){puts("cannot find the pid"); exit(-1);}
    closedir(procf);   
}

void func_s(char* pid){
    sprintf(buffer, "/proc/%s/stat", pid);
    fp = fopen(buffer, "r");
    fscanf(fp, "%s %s %s", temp, temp, temp);  // get the third string 
    printf("%s ", temp);
    fclose(fp);
}

void func_U(char* pid){
    sprintf(buffer, "/proc/%s/stat", pid);
    fp = fopen(buffer, "r");
    for (i = 0; i<13; i++){
        fscanf(fp, "%s", temp);
    }
    printf("utime=%s ", temp);
    fclose(fp);
}

void func_S(char* pid){
    sprintf(buffer, "/proc/%s/stat", pid);
    fp = fopen(buffer, "r");
    for (i = 0; i<14; i++){
        fscanf(fp, "%s", temp);
    }
    printf("stime=%s ", temp);
    fclose(fp);
}

void func_v(char* pid){
    sprintf(buffer, "/proc/%s/statm", pid);
    fp = fopen(buffer, "r");
    fscanf(fp, "%s", temp);
    printf("vmemory=%s ", temp);
    fclose(fp);
}

void func_c(char* pid){
    sprintf(buffer, "/proc/%s/cmdline", pid);
    fp = fopen(buffer, "r");
    fscanf(fp, "%[^\n]", temp);
    printf("[%s] ", temp);
    fclose(fp);
}

int cmpstring(const void* a, const void* b){  // for qsort
    return (atoi(a)-atoi(b));
}

int isnumber(char* arg){
    for (i = 0; i < strlen(arg); i++){
        if(*(arg + i) < '0' || *(arg + i) > '9') return 0; 
    }
    return 1;
}

void func_print(char* pid, int* param){
    if (param[0] == 1) func_p(pid);
    if (param[1] == 1) func_s(pid);
    if (param[2] == 1) func_U(pid);
    if (param[3] == 1) func_S(pid);
    if (param[4] == 1) func_v(pid);
    if (param[5] == 1) func_c(pid);
    printf("\n");
}

void func_all(int* param){
    int count = 0;
    char buf[1024];  // fix me
    char* ary[sizeof(char*)];  // fix me

    // load the user processes to an ary
    procf = opendir("/proc");
    while ((dp = readdir(procf)) != NULL){
        if(isnumber(dp -> d_name) == 1){  // found the pid) {  // found the number pid
           
            // extracting uid info
            sprintf(buf, "/proc/%s/status", dp -> d_name);
            fp = fopen(buf, "r");
            for (i = 0; i < 9; i++){  // get to the uid element
                fgets(temp, 50, fp);
            }
            fscanf(fp, "%s %s", temp, temp);  // extract second element in the line
            if (getuid() == atoi(temp)){  // checking uid are the same 
                ary[count] = dp -> d_name;  // if same load it to the ary
                count++;
            }
            fclose(fp);
        } 
    }

    // sorting ary in asceding order
    qsort(ary, count, sizeof(char*), cmpstring);

    int j;
    for(j = 0; j < count; j++){
        func_p(ary[j]);
        func_print(ary[j], param);
    }
}

int main (int argc, char* argv[]){
    char opt;
    char* pid = "";
    int flag_U = 0, flag_c = 0;
    int param[6] = {0, 0, 1, 0, 0, 1};  // index 0,1,2,3,4,5 means p, s, U, S, v, c. 0 means off 1 means on
    for(i = 1; i < argc; i++){  // checking for -U - situation
        if(strcmp(argv[i], "-") == 0){
            if (strcmp(argv[i-1], "-U") == 0) flag_U = 1;
            if (strcmp(argv[i-1], "-c") == 0) flag_c = 1;
        }
    }
    while ((opt = getopt(argc, argv, "p:s::U::S::v::c::")) != -1){
            if (opt == '?' || (optarg != NULL && (strcmp(optarg, "-") != 0) && isnumber(optarg)== 0)){
                puts("Invalid Option");
                exit(-1);
            }
            if (opt == 'p'){
                if (optarg == NULL){
                    puts("Invalid Argument");
                    exit(0);
                } else {
                    param[0] = 1;
                    pid = optarg;
                }
            } else if (opt == 's'){
                if (optarg == NULL) param[1] = 1;
            } else if (opt == 'U'){
                if (optarg != NULL || flag_U == 1) param[2] = 0; 
            } else if (opt == 'S'){
                if (optarg == NULL) param[3] = 1; 
            } else if (opt == 'v'){
                if (optarg == NULL) param[4] = 1;
            } else if (opt == 'c'){
                if (optarg != NULL || flag_c ==1) param[5] = 0;
            }
    }

    // determines prints out everything or given pid
    if(param[0] == 0){
        func_all(param);
    } else {
        func_print(pid, param);
    }
}
