#ifndef IMPL
#define IMPL

// standard limits of the following properties

#define HOST_NAME_SIZE_LIM 253
#define USER_NAME_SIZE_LIM 16
#define PATH_SIZE_LIM 4096
#define STD_STR_SIZE 30
#define MEM_INFO_LINE_SIZE 40

// Macro representation of the functions

#define USER 0
#define HOST 1
#define CWD 2
#define UPTIME 3
#define RAM 4
#define KERNEL 5

/*  USER, HOST, CWD, UPTIME, RAM, KERNEL */
static const char* icons[] = { "", "", "", "", "", ""};

static const int fetch_order[] = { CWD, USER, HOST, UPTIME, RAM , KERNEL };

#endif
