#include "drw.h"

char* print_module(const int module) {

	char* result = malloc(sizeof(char) * STD_STR_SIZE);
	switch(module) {

		case USER:
			sprintf(result, FETCH_COLOR " %s%suser:"   RESET   "     %s", icons[USER], LEFT_PAD, username());
			break;
		case HOST:
			sprintf(result, FETCH_COLOR " %s%shost:"   RESET   "     %s", icons[HOST], LEFT_PAD, hostname());
			break;
		case CWD:
			sprintf(result, FETCH_COLOR " %s%scwd:"    RESET  "      %s", icons[CWD], LEFT_PAD, cwd());
			break;
		case UPTIME:
			sprintf(result, FETCH_COLOR " %s%suptime:" RESET     "   %s", icons[UPTIME], LEFT_PAD, uptime());
			break;
		case RAM:
			sprintf(result, FETCH_COLOR " %s%sram:"    RESET  "      %s", icons[RAM], LEFT_PAD, ram());
			break;
		case KERNEL:
			sprintf(result, FETCH_COLOR " %s%skernel:" RESET     "   %s", icons[KERNEL], LEFT_PAD, kernel());
			break;
		case DE:
			sprintf(result, FETCH_COLOR " %s%sde:"     RESET "       %s", icons[DE], LEFT_PAD, wmde());
			break;
		case PALETTE:
			sprintf(result, "%s%s", LEFT_PAD, palette());
			break;
		default:
			struct SCRIPT script = external(module);
			char* buf = cmd(script.path);	
			sprintf(result,  " %s%s%s:      %s", script.icon, LEFT_PAD, script.name, buf);
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
		printf(LOGO_COLOR "%s" RESET "%s\n", tux[i], print_module(fetch_order[i]));

	if (printspaces) {
		for(int i = LOGO_LINES; i < module_count; i++) {
			for(int j = 0; j < LOGO_COLUMNS; j++)
				printf(" ");

			printf("%s\n", print_module(fetch_order[i]));
		}
	} else {
		for(int i = module_count; i < LOGO_LINES; i++) 
			printf(LOGO_COLOR "%s\n" RESET, tux[i]);
	}

}
