#ifndef IMPL
#define IMPL

// standard limits of the following properties

#define HOST_NAME_SIZE_LIM 253
#define USER_NAME_SIZE_LIM 16
#define PATH_SIZE_LIM 4096
#define STD_STR_SIZE 30

// Make sure you use a nerd font in order for these to work

#define HOST_ICON " "
#define USER_ICON " "
#define UPTIME_ICON " " 
#define CWD_ICON " "

// Macro representation of the functions

#define USER 0
#define HOST 1
#define CWD 2
#define UPTIME 3

static const int fetch_order[] = { USER, HOST, CWD, UPTIME };

#endif
