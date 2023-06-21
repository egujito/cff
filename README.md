# 🚀 CFF - C Fast Fetch
A fetch that aims to run as fast as possible. Developed for fun (and for GNU/Linux systems).

(_The following example shows the fetch running with the respective icons set in `cfetch.h`_)

![](https://raw.githubusercontent.com/egujito/cff/master/example-og.png)

_Blazingly fast  🏎️💨_

### Building:

```
$ make
```

### Cleaning:

```
$ make clean
```

### Running:

```
$ ./cff
```

# `cfetch.h`

### Variables and Macros:

`LEFT_PAD`: If you define icons in icons[], makes sure you set this to " " so the module name doesn't stick to the icon.
`static const char* icons[]`: You can define the icons to the builtin modules here,

`static const int fetch_order[]`: You can define the order of the fetch here. The default one is:
```c
static const int fetch_order[] = { USER, HOST, CWD, UPTIME, RAM, KERNEL, DE };
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
- The buffer that is allocated to store the script output is equal to 32
- Cfetch only reads the first line of the output of the script
- Using external scripts might hurt the execution time which goes against the first premisse of this program ("to run as fast as possible")

### Modules:

Module        | Usage
------------- | -------------
HOST  	      | Hostname of the OS
USER  	      | Current user name
UPTIME        | Seconds since boot
CWD           | Current working directory
KERNEL        | Kernel release
RAM           | Total Ram
EXTERNAL + i  | Executes and gets the output of `scripts[i]`

## TODO:

- [ ]  Add and update more modules:
- [x] release name
- [x] external scripting
- [x]  Add Fetch ASCII ART
# 🚀 CFF - C Fast Fetch
A fetch that aims to run as fast as possible. Developed for fun (and for GNU/Linux systems).

(_The following example shows the fetch running with the respective icons set in `cfetch.h`_)

![](https://raw.githubusercontent.com/egujito/cff/master/example-og.png)

_Blazingly fast  🏎️💨_

### Building:

```
$ make
```

### Cleaning:

```
$ make clean
```

### Running:

```
$ ./cff
```

## Modules:

Currently CFF has the following modules:

Module  | Usage
------------- | -------------
HOST  	| Hostname of the OS
USER  	| Current user name
UPTIME  | Seconds since boot
CWD     | Current working directory
KERNEL  | Kernel release
RAM | Total Ram


## TODO:

- [ ]  Add and update more modules:
		- release name;
		- external scripting
- [x]  Add Fetch ASCII ART
