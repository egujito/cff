#ifndef DRW_H
#define DRW_H

#include <stdio.h>
#include <stdlib.h>
#include "cfetch.h"
#include "config.h"
#include "api.h"

#define LOGO_LINES 7
#define LOGO_COLUMNS 11

static const char* tux[] = {
	"   .--.    ",
	"  |o_o |   ",
	"  |:_/ |   ",
	" //   \\ \\  ",
	"(|     | ) ",
	"/'\\_   _/`\\",
	"\\___)=(___/"
};


char* print_module(const int module);
void fetch();

#endif
