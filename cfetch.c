#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sysinfo.h>
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

// RAM NOT IMPLEMENTED 

char* ram() {

	struct sysinfo* snapshot = malloc(sizeof(struct sysinfo));
	int c = sysinfo(snapshot);

	if (c != 0) {
		return "Error while using RAM module \n";	
	} 
	
	char* r = malloc(sizeof(char) * 50); 
	sprintf(r, "%lf/%lf", ((double)snapshot->totalram * (double)9.31*0.0000000001) - ((double)snapshot->freeram * (double)9.31*0.0000000001),
			snapshot->totalram * (double)9.31*0.0000000001);
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
				printf("%s user:    %s \n", USER_ICON, username());
				break;
			case HOST:
				printf("%s host:    %s \n", HOST_ICON, hostname());
				break;
			case CWD:
				printf("%s cwd:     %s \n", CWD_ICON, cwd());
				break;
			case UPTIME:
				printf("%s uptime:  %s \n", UPTIME_ICON, timeformat(uptime()));
				break;
			case 4:
				printf("%s ram:     %s \n", RAM_ICON, ram());
		}
	}
}

int main(int argc, char* argv[]) {

	fetch();

	return 0;

}
