#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "cfetch.h"


char* gethost() {

    FILE *hostfile = fopen("/etc/hostname", "r");
    
    if (hostfile == NULL) return "err";

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

int main(int argc, char* argv[]) {
    
    printf("%s host: %s", HOST_ICON, gethost());
    printf("%s user: %s", USER_ICON, username());

    return 0;

}
