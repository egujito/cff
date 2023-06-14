#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <linux/kernel.h>
#include "cfetch.h"



char* hostname() {

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

	return snapshot->uptime; //seconds

}

char* timeformat(long full) {

	char* r = malloc(sizeof(char) * STD_STR_SIZE);
	float h;
	int m;

	if (full / 60 > 60) {

		h = (float)full / (float)3600;  // gets the hours
		float p = h - (int)h;           // calculate percentage to multiply by 60 to get minutes
		m = p * 60;                     // calculates minutes (0 <= m < 60)

	} else {

		h++;
		m = 0;

	}

	sprintf(r, "%dh %dm", (int)h, m);

	return r; 

}

void fetch() {

	const int lines = sizeof(fetch_order) / sizeof(int);

	for(int i = 0; i < lines; i++) {
		switch(fetch_order[i]) {
			case 0:
				printf("%s user:    %s \n", USER_ICON, username());
				break;
			case 1:
				printf("%s host:    %s \n", HOST_ICON, hostname());
				break;
			case 2:
				printf("%s cwd:     %s \n", CWD_ICON, cwd());
				break;
			case 3:
				printf("%s uptime:  %s \n", UPTIME_ICON, timeformat(uptime()));
				break;
		}
	}

}

int main(int argc, char* argv[]) {

	fetch();

	return 0;

}
