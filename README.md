# upath

Version 1.0

     Usage: upath [-options] [envname..]
      --help | -h        Help info.
      --version | -V     Version info.
 
 By default, environment variable PATH is assumed:
 
 
 # What it Does
 
upath examines your environment variable, noting the order of the colon separated components. It then emits the components with the same ordering, but with duplicate directories eliminated.

After adding a directory to PATH for example, you can eliminate duplicates by doing:

PATH=$(upath)

Or for a different variable LD_LIBRARY_PATH:

LD_LIBRARY_PATH=$(upath LD_LIBRARY_PATH)
