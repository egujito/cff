#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "cfetch.h"


char* gethost() {

    FILE *hostfile = fopen(HOST_NAME_PATH, "r");
    
    if (hostfile == NULL) return "Error while getting hostname";

    char *content = malloc (sizeof(char) * HOST_NAME_SIZE_LIM);

    fgets(content, 253, hostfile);
    fclose(hostfile);

    return content;

}

char* username() {
    
    char* content = malloc (sizeof(char) * USER_NAME_SIZE_LIM); 
    content = getlogin();
    return content;

}

char* cwd() {

    char* content = malloc (sizeof(char) * PATH_NAME_SIZE_LIM);
    getcwd(content, PATH_NAME_SIZE_LIM);
    return content;

}

int main(int argc, char* argv[]) {
    
    printf("%s host: %s", HOST_ICON, gethost());
    printf("%s user: %s \n", USER_ICON, username());
    printf("%s cwd:  %s", PATH_ICON, cwd());

    return 0;

}
