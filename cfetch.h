#ifndef IMPL
#define IMPL

// standard limits of the following properties

#define HOST_NAME_SIZE_LIM 253
#define USER_NAME_SIZE_LIM 16
#define PATH_SIZE_LIM 4096
#define STD_STR_SIZE 32
#define MEM_INFO_LINE_SIZE 30

#define LEFT_PAD "" // when setting icons in <static const char* icons[]> make sure you set this to " ";
					// if you do not use icons the fetch modules text will be docked to the left side of the icon

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

static const char* icons[] = { "", "", "", "", "", "", "" };

/*   0  ,  1  ,  2 ,    3  ,  4 ,   5   , 6  ,    7 + index of script in scripts[]         */
/*  USER, HOST, CWD, UPTIME, RAM, KERNEL, DE ,               EXTERNAL                         */

static const int fetch_order[] = { USER, HOST, CWD, UPTIME, RAM, KERNEL, DE, EXTERNAL+0 }; // customize order
																			   
static struct SCRIPT scripts[] = {
	{ "~/dev/cfetch/ram.sh", "", "ram" }
};

#endif
