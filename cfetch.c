#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <sys/utsname.h>
#include <linux/kernel.h>
#include "cfetch.h"
#include "logo.h"
#include "config.h"

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

char* print_module(const int module) {

	char* result = malloc(sizeof(char) * STD_STR_SIZE);

	switch(module) {
		case USER:
			sprintf(result, " %s%s" FETCH_COLOR "user:"   RESET "     %s", icons[USER], LEFT_PAD, username());
			break;
		case HOST:
			sprintf(result, " %s%s" FETCH_COLOR "host:"   RESET "     %s", icons[HOST], LEFT_PAD, hostname());
			break;
		case CWD:
			sprintf(result, " %s%s" FETCH_COLOR "cwd:"    RESET "      %s", icons[CWD], LEFT_PAD, cwd());
			break;
		case UPTIME:
			sprintf(result, " %s%s" FETCH_COLOR "uptime:" RESET "   %s", icons[UPTIME], LEFT_PAD, uptime());
			break;
		case RAM:
			sprintf(result, " %s%s" FETCH_COLOR "ram:"    RESET "      %s", icons[RAM], LEFT_PAD, ram());
			break;
		case KERNEL:
			sprintf(result, " %s%s" FETCH_COLOR "kernel:" RESET "   %s", icons[KERNEL], LEFT_PAD, kernel());
			break;
		case DE:
			sprintf(result, " %s%s" FETCH_COLOR "de:"     RESET "       %s", icons[DE], LEFT_PAD, wmde());
			break;
		default:
			struct SCRIPT script = external(module);
			char* buf = cmd(script.path);	
			sprintf(result,  " %s%s%s:      %s", script.icon, LEFT_PAD, script.name, buf);
			break;
	}

	return result;
}

void pallete() {
	
	for (int i = 0; i < LOGO_COLUMNS + 2; ++i) {
		printf(" ");
	}

	printf(RED    "●  "     RESET);
	printf(YELLOW "●  "     RESET);
	printf(GREEN  "●  "     RESET);
	printf(CYAN   "●  "     RESET);
	printf(BLUE   "●  "     RESET);
	printf(MAGENTA"●\n"     RESET);

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

	pallete();

}

int main(int argc, char* argv[]) {

	fetch();

	return 0;

}
