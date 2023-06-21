#ifndef CFETCH_H
#define CFETCH_H

// standard limits of the following properties

#define HOST_NAME_SIZE_LIM 253
#define USER_NAME_SIZE_LIM 16
#define PATH_SIZE_LIM 4096
#define STD_STR_SIZE 32
#define MEM_INFO_LINE_SIZE 30


// Macro representation of the modules

#define USER 0
#define HOST 1
#define CWD 2
#define UPTIME 3
#define RAM 4
#define KERNEL 5
#define DE 6
#define EXTERNAL 7


struct SCRIPT {
	char* path;
	char* icon;
	char* name;
};

#endif
