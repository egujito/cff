#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <sys/utsname.h>
#include <linux/kernel.h>
#include "cfetch.h"
#include "logo.h"

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
		return "Error while retrieving <struct utsname*> \n"; // TODO: better error handling
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

char* print_module(int module) {
	char* result = malloc(sizeof(char) * STD_STR_SIZE);

	switch(module) {
		case USER:
			sprintf(result, " %s%suser:     %s", icons[USER], LEFT_PAD, username());
			break;
		case HOST:
			sprintf(result, " %s%shost:     %s", icons[HOST], LEFT_PAD, hostname());
			break;
		case CWD:
			sprintf(result, " %s%scwd:      %s", icons[CWD], LEFT_PAD, cwd());
			break;
		case UPTIME:
			sprintf(result, " %s%suptime:   %s", icons[UPTIME], LEFT_PAD, uptime());
			break;
		case RAM:
			sprintf(result, " %s%sram:      %s", icons[RAM], LEFT_PAD, ram());
			break;
		case KERNEL:
			sprintf(result, " %s%skernel:   %s", icons[KERNEL], LEFT_PAD, kernel());
			break;
		case DE:
			sprintf(result, " %s%sde:       %s", icons[DE], LEFT_PAD, wmde());
			break;
	}

	return result;
}

void fetch() {

	const int module_count = sizeof(fetch_order) / sizeof(int);
	int looplim = module_count;
	int printspaces = 0;

	if(module_count > LOGO_LINES) {
		looplim = LOGO_LINES;
		printspaces = 1;
	}

	for(int i = 0; i < looplim; i++)
		printf("%s %s\n", tux[i], print_module(fetch_order[i]));

	if (printspaces) {
		for(int i = LOGO_LINES; i < module_count; i++) {
			for(int j = 0; j < LOGO_COLUMNS + 1; j++)
				printf(" ");

			printf("%s\n", print_module(fetch_order[i]));
		}
	} else {
		for(int i = module_count; i < LOGO_LINES; i++) 
			printf("%s\n", tux[i]);
	}

}

int main(int argc, char* argv[]) {

	fetch();

	return 0;

}
