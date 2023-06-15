# CFF - C Fast Fetch
A fetch that aims to run as fast as possible. Developed for fun (and for GNU/Linux systems).

![](https://raw.githubusercontent.com/egujito/cff/master/example-og.png)
![](https://raw.githubusercontent.com/egujito/cff/master/speed.png)
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

## TODO:

- [ ]  Add and update more modules:
		- Detect window manager
		- OS release name
- [ ]  Add Fetch ASCII ART

