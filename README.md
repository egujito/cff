# 🚀 CFF - C Fast Fetch
A fetch that aims to run as fast as possible. Developed for fun (and for GNU/Linux systems).

![](https://raw.githubusercontent.com/egujito/cff/master/cff.png)

_Blazingly fast  🏎️💨_

#### Building:

```bash
$ make
```

#### Cleaning:

```bash
$ make clean
```

#### Running (locally):

```bash
$ ./cff
```

#### Installing/Uninstalling:

```bash
$ sudo make install

$ sudo make uninstall
```
#### Running:

```bash
$ cff
```

# `config.h`

### Variables and Macros:

`LEFT_PAD`: If you define icons in icons[], makes sure you set this to " " so the module name doesn't stick to the icon. (Default: "")

`FETCH_COLOR`: sets the color to the names of the modules (Default: BLUE)

`LOGO_COLOR`: sets the color the logo of the fetch. (Default: CYAN)

`static const char* icons[]`: You can define the icons to the builtin modules here,
Default:
```c
static const char* icons[] = { "", "", "", "", "", "", "" };
```

`static const int fetch_order[]`: You can define the order of the fetch here. The default one is:

```c
static const int fetch_order[] = { USER, HOST, CWD, UPTIME, RAM, KERNEL, DE, PALETTE };
```

`static struct SCRIPT scripts[]`: Here is where external scripts go. This array is of the SCRIPT datatype which has 3 attributes:

```c
struct SCRIPT {
	char* path;
	char* icon;
	char* name;
};

```
If you wish to add an external script first you add it to the scripts array:

```c
static struct SCRIPT scripts[] = {
	{ "path/to/script", "script icon", "script name (the name that shows on the fetch)" }
};
```

Then you add `EXTERNAL+i` to the `fetch_order` array, where the i is equal to the index of your script in the `scripts` array. 

⚠️ Keep in mind the following when using external scripts:
- The buffer that is allocated to store the script output is equal to 128;
- Only the first line of the output of the script is read;
- Using external scripts might hurt the execution time which goes against the first premise of this program ("to run as fast as possible").

### Modules:

Macro        | Usage
------------- | -------------
HOST  	      | Hostname of the OS
USER  	      | Current user name
UPTIME        | Seconds since boot
CWD           | Current working directory
KERNEL        | Kernel release
RAM           | Total Ram
EXTERNAL + i  | Executes and gets the output of `scripts[i]`
PALETTE       | Prints the color palette. Should be at the end of `fetch_order[]`

## TODO:

- [ ]  Add and update more modules:
- [x] release name
- [x] external scripting
- [x]  Add Fetch ASCII ART
- [x] Color support

### My Personal `config.h`:
Make sure you use a patched font for the icons.
```c
#ifndef CONFIG_H
#define CONFIG_H

#include "cfetch.h"

#define LEFT_PAD " " // when setting icons in <static const char* icons[]> make sure you set this to " ";
                    // if you do not use icons the fetch modules text will be docked to the left side of the icon

#define FETCH_COLOR  BLUE
#define LOGO_COLOR   CYAN

static const char* icons[] = { "", "󰒋", "", "", "󰍛", "", "" };

/*   0  ,  1  ,  2 ,    3  ,  4 ,   5   , 6 ,    7   ,    8 + index of script in scripts[]         */
/*  USER, HOST, CWD, UPTIME, RAM, KERNEL, DE, PALLETE, EXTERNAL    + i                             */

static const int fetch_order[] = { USER, HOST, UPTIME, RAM, KERNEL, DE, PALETTE }; // customize order

static struct SCRIPT scripts[] = {};

#endif
```
