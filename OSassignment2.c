#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <dirent.h>

int main(int argc, char * argv[]){
    // for(int i = 1 ; i < argc ; i++){
    //     printf("%s\n",argv[i]);
    // }
    char str[1000];
    char* arr[100];
    while(1){
        printf("shell>");
        fgets(str,1000,stdin);
        char* p = strtok(str, " ");
        int i = 0;                                   //i is defined here
        while(p != NULL){
            arr[i++] = p;
            p = strtok(NULL, " ");
        }

        if(strcmp(arr[0],"echo") == 0){        //echo yaha chal rha
            for(int j = 1 ;j < i ; j++){
            printf("%s ",arr[j]);
            }
        }
        
        else if(strcmp("pwd\n",arr[0]) == 0 || strcmp("pwd",arr[0]) == 0){
            
            char path[1000];

            if (getcwd(path, sizeof(path)) == NULL){
                perror("getcwd() error");
            }
            else{
                printf("%s\n", path);
            }

        }

        else if(strcmp("cd",arr[0]) == 0 || strcmp(("cd.."),arr[0]) == 0){   //arr[1] shouldnt have \n in the end, remove /n with " " by adding space before entering
            
            if(strcmp("cd..",arr[0]) == 0){
                chdir("..");
            }
            else{
                chdir(arr[1]);
                char path[1000];

                if (getcwd(path, sizeof(path)) == NULL){
                    perror("getcwd() error");
                }
                else{
                    printf("%s\n", path);
                }
            }

        }

        else if(strcmp("mkdir",arr[0]) == 0){ //simple command for making a directory
        //one more flag is remaning#########################################

            if (strcmp("-p",arr[1]) == 0){ //case 1 : multiple parent directories are missing

                char * p2 = strtok(arr[2],"\\");

                int k = 0;

                char * arr2[100];

                while(p2 != NULL){ ////p2 is null ?
                    arr2[k] = p2;
                    k++;
                    p2 = strtok(NULL,"\\");
                }

                int g = 0;
                while(g < k){
                    if(chdir(arr2[g]) != 0){
                        mkdir(arr2[g]);
                        chdir(arr2[g]);
                    }
                    g++;
                }

                while(k > 0){
                    chdir("..");
                    k--;
                }
            }

            else{ //base case
                int check = mkdir(arr[1]);
                if(check == 0){
                    printf("done successfully\n");
                }
                else{
                    printf("to make nested directories add -p to command \n");
                }
            }
        }

        else if(strcmp(arr[0],"cat") == 0){ //working command for cat
            if(strcmp(arr[1],"-n") == 0){ //for printing line number
                FILE* ptr;
                char c;
                //create the path of the file here
                ptr = fopen(arr[2],"r");
                if(ptr == NULL){
                    perror("Cannot open file\n");
                }
                else{
                    c = fgetc(ptr);
                    int z = 1;
                    printf("%d) ",z++);
                    while(c != EOF){
                        printf("%c",c);
                        if(c == '\n'){
                            printf("%d) ",z++);
                        }
                        c = fgetc(ptr);
                    }
                    fclose(ptr);
                    printf("\n");
                }
            }
            else{ //for printing multiple files 
                for(int t = 1 ; t < i ; t++){
                    FILE* ptr;
                    char c;
                    ptr = fopen(arr[t],"r");
                    if(ptr == NULL){
                        perror("Cannot open file,not in directory\n");
                    }
                    else{
                        c = fgetc(ptr);
                        while(c != EOF){
                            printf("%c",c);
                            c = fgetc(ptr);
                        }
                        fclose(ptr);
                    }
                }
            }
        }

        else if(strcmp("date\n",arr[0]) == 0 || strcmp(arr[0],"date") == 0){
            time_t t;

            if(strcmp(arr[1],"-I") == 0 || strcmp(arr[1],"-I\n") == 0){ //one function is remaining
                t = time(NULL);
                struct tm bruh = *localtime(&t);
                printf("%d-%d-%d\n",bruh.tm_year + 1900,bruh.tm_mon+1,bruh.tm_mday);
            }
            else if(strcmp(arr[1],"-u") == 0 || strcmp(arr[1],"-u\n") == 0){
                struct tm * UTC;
                t = time(NULL);
                UTC = gmtime(&t);
                printf("%s",asctime(UTC));
            }
            else{
                time(&t);
                char *bruh = "";
                bruh = ctime(&t);
                printf("%s",bruh);
            }
        }

        else if(strcmp("ls\n",arr[0]) == 0 || strcmp("ls",arr[0]) == 0){
            if(strcmp("-a",arr[1]) == 0 || strcmp("-a\n",arr[0]) == 0){ //flag to print 
                DIR* ptr;
                struct dirent *current;
                ptr = opendir(".");
                if(ptr == NULL){
                    perror("directory could not be opened\n");
                }
                else{
                    int m = 0;
                    while((current = readdir(ptr)) != NULL){
                        printf("%s   ",current->d_name);
                        m++;
                        if(m == 4){
                            printf("\n");
                            m = 0;
                        }
                    }
                    if(closedir(ptr) == -1){
                        perror("error closing directory");
                    }
                }
            }

            else if(strcmp("-l",arr[1]) == 0 || strcmp("-l\n",arr[1]) == 0){
                DIR* ptr;
                struct dirent *current;
                ptr = opendir(".");
                if(ptr == NULL){
                    perror("directory could not be opened\n");
                }
                else{
                    while((current = readdir(ptr)) != NULL){
                        if(current->d_name[0] != '.'){
                            printf("%s\n",current->d_name);
                        }
                    }
                    if(closedir(ptr) == -1){
                        perror("error closing directory");
                    }
                }
            }

            else{
                DIR* ptr;
                struct dirent *current;
                ptr = opendir(".");
                if(ptr == NULL){
                    perror("directory could not be opened\n");
                }
                else{
                    int m = 0;
                    while((current = readdir(ptr)) != NULL){
                        if(current->d_name[0] != '.'){
                            printf("%s   ",current->d_name);
                            m++;
                        }
                        if(m == 4){
                            printf("\n");
                            m = 0;
                        }
                    }
                    if(closedir(ptr) == -1){
                        perror("error closing directory");
                    }
                }
            }
        }
        else if(strcmp("rm\n",arr[0]) == 0 || (strcmp(arr[0],"rm") == 0 && arr[1] == NULL)){
            printf("no directory/file given to delete");
        }
        
        // else if(strcmp("rm",arr[0]) == 0){
            
        // }
    }
    return 0;
}
