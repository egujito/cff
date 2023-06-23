#ifndef CFETCH_H
#define CFETCH_H

// standard limits of the following properties

#define HOST_NAME_SIZE_LIM 253
#define USER_NAME_SIZE_LIM 16
#define PATH_SIZE_LIM 4096
#define STD_STR_SIZE 128
#define MEM_INFO_LINE_SIZE 30


// Macro representation of the modules

#define USER 0
#define HOST 1
#define CWD 2
#define UPTIME 3
#define RAM 4
#define KERNEL 5
#define DE 6
#define PALLETE 7
#define EXTERNAL 8


struct SCRIPT {
	char* path;
	char* icon;
	char* name;
};


#define BLACK "\033[30m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define RESET "\033[0m"

#endif
