# upath

Version 1.0

Usage: upath [-options] [envname..]
 --help | -h		Help info.
 --version | -V		Version info.
 
 By default, environment variable PATH is assumed:
 
 upath
 
 # What it Does
 
upath examines your environment variable, noting the order of the colon separated components. It emits the same ordering, with all of the duplicate directories eliminated.
