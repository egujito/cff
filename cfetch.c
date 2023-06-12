#include <stdio.h>
#include <stdlib.h>
#include "cfetch.h"


char* gethost() {

    FILE *hostfile = fopen("/etc/hostname", "r");
    
    if (hostfile == NULL) return "err";

    char *content = malloc (sizeof(char) * HOST_NAME_SIZE_LIM);

    fgets(content, 253, hostfile);
    fclose(hostfile);

    return content;

}


int main(int argc, char* argv[]) {
    
    printf("host: %s", gethost());

    return 0;

}
