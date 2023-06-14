#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <linux/kernel.h>
#include "cfetch.h"


char* host() {

    char* host = malloc (sizeof(char) * HOST_NAME_SIZE_LIM);
    int r = gethostname(host, HOST_NAME_SIZE_LIM); 
    if (r != 0) {
        return "Error while retrieving hostname \n";
    }
    return host;

}

char* username() {
    
    char* username = malloc (sizeof(char) * USER_NAME_SIZE_LIM); 
    username = getlogin();
    return username;

}

char* cwd() {

    char* cwd = malloc (sizeof(char) * PATH_SIZE_LIM);
    getcwd(cwd, PATH_SIZE_LIM);
    if (cwd == NULL) {
        return "Error while retrieving current working directory \n";
    }

    return cwd;

}

long uptime() {
   
    struct sysinfo* snapshot = malloc(sizeof(struct sysinfo));
    int r = sysinfo(snapshot);

    if (r != 0) {
        return 1; // TODO: better error handling
    } 

    return snapshot->uptime / 60; // TODO: implement correct format
        
}

int main(int argc, char* argv[]) {
    
    printf("%s host: %s \n", HOST_ICON, host());
    printf("%s user: %s \n", USER_ICON, username());
    printf("%s cwd:  %s \n", PATH_ICON, cwd());
    printf("%s uptime: %ld mins \n", UPTIME_ICON, uptime());

    return 0;

}
