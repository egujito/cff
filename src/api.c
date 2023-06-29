#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <sys/utsname.h>
#include <linux/kernel.h>
#include "cfetch.h"
#include "config.h"
#include "api.h"

char* hostname() {

	char* host = malloc (sizeof(char) * HOST_NAME_SIZE_LIM);
	int c = gethostname(host, HOST_NAME_SIZE_LIM); 

	if (c != 0) {
		return "Error while retrieving hostname";
	}

	return host;

}

char* username() {

	char* username = malloc (sizeof(char) * USER_NAME_SIZE_LIM); 
	username = getlogin();

	if (username == NULL) return "Error while retrieving username";

	return username;

}

char* cwd() {

	char* cwd = malloc (sizeof(char) * PATH_SIZE_LIM);
	getcwd(cwd, PATH_SIZE_LIM);

	if (cwd == NULL) {
		return "Error while retrieving current working directory";
	}

	return cwd;

}

char* uptime() {

	struct sysinfo* snapshot = malloc(sizeof(struct sysinfo));
	int c = sysinfo(snapshot);

	if (c != 0) {
		return "Error while getting <struct sysinfo*>"; // TODO: better error handling
	}

	int seconds = snapshot->uptime;
	int hours = seconds / 3600;
	seconds = seconds % 3600;
	int minutes = seconds / 60;
	
	free(snapshot);

	char* result = malloc(sizeof(char) * STD_STR_SIZE);

	sprintf(result, "%02dh:%02dm", hours, minutes);

	return result;

}

char* kernel() {

	struct utsname* snapshot = malloc(sizeof(struct utsname));
	int c = uname(snapshot);

	if (c != 0) {
		return "Error while retrieving <struct utsname*>"; // TODO: better error handling
	}

	return snapshot->release;
}

char* wmde() {

	char* r = getenv("DESKTOP_SESSION");

	if(r != NULL) {
		return r;
	}

	r = getenv("XDG_CURRENT_DESKTOP");

	if(r != NULL) {
		return r;
	}

	return "Could not get Window manager/Desktop environment";

}

// !! RAM ONLY RETURNS TOTAL AVAILABLE RAM NOT THE RAM BEING USED
char* ram() {
	
	struct sysinfo* snapshot = malloc(sizeof(struct sysinfo));
	int c = sysinfo(snapshot);

	if (c != 0) {
		return "Error while getting <struct sysinfo*>";
	} 

	char* r = malloc(sizeof(char) * STD_STR_SIZE);
	sprintf(r, "%.2f GB", (float) (snapshot->totalram * (double)9.31*0.0000000001));

	free(snapshot);

	return r;

}

struct SCRIPT external(int total) {
	int i = total - EXTERNAL;
	struct SCRIPT r;
	r.path=scripts[i].path;
	r.icon=scripts[i].icon;
	r.name=scripts[i].name;
	return r;
}

char* cmd(const char* path) {

	char* r = malloc(sizeof(char) * STD_STR_SIZE);
	FILE* f = popen(path, "r");
	fgets(r, sizeof(r), f);
	fclose(f);
	return r;

}

char* palette() {

	char* result = malloc(sizeof(char) * STD_STR_SIZE);
	
	sprintf(result,
		RED     "●  " RESET
		YELLOW  "●  " RESET
		GREEN   "●  " RESET
		CYAN    "●  " RESET
		BLUE    "●  " RESET
		MAGENTA "●"   RESET
	);

	return result;

}
