#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/sysinfo.h>
#include <sys/utsname.h>
#include <sys/resource.h>
#include <linux/kernel.h>
#include "cfetch.h"



char* hostname() {

	char* host = malloc (sizeof(char) * HOST_NAME_SIZE_LIM);
	int c = gethostname(host, HOST_NAME_SIZE_LIM); 

	if (c != 0) {
		return "Error while retrieving hostname \n";
	}

	return host;

}

char* username() {

	char* username = malloc (sizeof(char) * USER_NAME_SIZE_LIM); 
	username = getlogin();

	if (username == NULL) return "Error while retrieving username \n";

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

char* uptime() {

	struct sysinfo* snapshot = malloc(sizeof(struct sysinfo));
	int c = sysinfo(snapshot);

	if (c != 0) {
		return ""; // TODO: better error handling
	}

	int seconds = snapshot->uptime;
	int hours = seconds / 3600;
	seconds = seconds % 3600;
	int minutes = seconds / 60;

	char* result;

	sprintf(result, "%02d:%02d", hours, minutes);

	return result;

}

char* kernel() {

	struct utsname* snapshot = malloc(sizeof(struct utsname));
	int c = uname(snapshot);

	if (c != 0) {
		return "Error while retrieving kernel release \n"; // TODO: better error handling
	}
	
	return snapshot->release;
}

void strip(char* s) {
	int i = 0, j = 0;

    while (s[i]) {
        if (s[i] != ' ') {
            s[j] = s[i];
            j++;
        }
        i++;
    }
    s[j] = '\0';
}

// NOT IMPL YET
char* ram() {

	size_t len = STD_STR_SIZE * 3;

	FILE *meminfo = fopen("/proc/meminfo", "r");
	if (meminfo == NULL) return "Failed to open /proc/meminfo";

	char* memtotalline = malloc(sizeof(char) * MEM_INFO_LINE_SIZE);
	char memavailableline[MEM_INFO_LINE_SIZE];
	getline(&memtotalline, &len, meminfo);
	//getline(&memavailableline, &len, meminfo);
	
	int n = 2;
	int i = 1;

    while (fgets(memavailableline, sizeof(memavailableline), meminfo) != NULL) {
        if (i == n) {
            // printf("%s", memavailableline);
            break;
        }
        i++;
    }


	fclose(meminfo);

	char* total = malloc(sizeof(char) * STD_STR_SIZE);

	strncpy(total, memtotalline + 9, 24 - 9 + 1);
	total[24-9-1] = '\0';

	strip(total);
	

	char* r = malloc(sizeof(char) * STD_STR_SIZE);
	sprintf(r, "%d GB", (atoi(total) / 100000));

	return r;
}

void fetch() {

	const int lines = sizeof(fetch_order) / sizeof(int);

	for(int i = 0; i < lines; i++) {
		switch(fetch_order[i]) {
			case USER:
				printf("%s user:     %s \n", icons[USER], username());
				break;
			case HOST:
				printf("%s host:     %s \n", icons[HOST], hostname());
				break;
			case CWD:
				printf("%s cwd:      %s \n", icons[CWD], cwd());
				break;
			case UPTIME:
				printf("%s uptime:   %s \n", icons[UPTIME], uptime());
				break;
			case RAM:
				printf("%s ram:      %s \n", icons[RAM], ram());
				break;
			case KERNEL:
				printf("%s kernel:   %s \n", icons[KERNEL], kernel());
				break;
		}
	}
}

int main(int argc, char* argv[]) {

	fetch();

	return 0;

}
