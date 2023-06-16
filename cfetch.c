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

long uptime() {

	struct sysinfo* snapshot = malloc(sizeof(struct sysinfo));
	int c = sysinfo(snapshot);

	if (c != 0) {
		return 1; // TODO: better error handling
	} 

	return snapshot->uptime; //seconds

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

	size_t len = 40;

	FILE *meminfo = fopen("/proc/meminfo", "r");
	if (meminfo == NULL) return "Failed to open /proc/meminfo";

	char* memtotalline = malloc(sizeof(char) * MEM_INFO_LINE_SIZE);
	//char* memavailableline = malloc(sizeof(char) * MEM_INFO_LINE_SIZE);

	getline(&memtotalline, &len, meminfo);
	//getline(&memavailableline, &len, meminfo);

	fclose(meminfo);

	char* total = malloc(sizeof(char) * STD_STR_SIZE);
	//char* available = malloc(sizeof(char) * STD_STR_SIZE);

	strncpy(total, memtotalline + 9, 24 - 9 + 1);
	total[24-9-1] = '\0';

	//strncpy(available, memavailableline + 12, 24 - 12 + 1);
	//available[24-12-1] = '\0';

	
	strip(total);
	//strip(available);

	char* r = malloc(sizeof(char) * STD_STR_SIZE);
	sprintf(r, "%d GB", (atoi(total) / 100000));

	return r;
}

char* timeformat(long full) {

	char* r = malloc(sizeof(char) * STD_STR_SIZE);
	float h;
	int m;

	if (full / 60 > 60) {

		h = (float)full / (float)3600;  
		float p = h - (int)h;           
		m = p * 60;						
										
	} else {
		
		if (full / 60 == 60) {

			m = 0;
			h = 1;

		} else {

			m = full / 60;
			h = 0;

		}
	}

	sprintf(r, "%dh %dm", (int)h, m);

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
				printf("%s uptime:   %s \n", icons[UPTIME], timeformat(uptime()));
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
