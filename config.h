#ifndef CONFIG_H
#define CONFIG_H

#include "cfetch.h"

#define LEFT_PAD "" // when setting icons in <static const char* icons[]> make sure you set this to " ";
                    // if you do not use icons the fetch modules text will be docked to the left side of the icon

#define FETCH_COLOR BLUE

static const char* icons[] = { "", "", "", "", "", "", "" };

/*   0  ,  1  ,  2 ,    3  ,  4 ,   5   , 6  ,    7 + index of script in scripts[]         */
/*  USER, HOST, CWD, UPTIME, RAM, KERNEL, DE ,               EXTERNAL                      */
static const int fetch_order[] = { USER, HOST, CWD, UPTIME, RAM, KERNEL, DE }; // customize order

static struct SCRIPT scripts[] = {};

#endif
