# simple-in-memory-filesystem
**SIMF**(Simple In-memory Filesystem) is a filesystem that runs on **FUSE**(Filesystem in User Space).  
*According to the following [Wikipedia](https://en.wikipedia.org/wiki/Filesystem_in_Userspace) article:-*  
>**F**ilesystem in **USE**rspace is a software interface for Unix and Unix-like computer operating systems  
>that lets non-privileged users create their own file systems without editing kernel code.  


**SIMF** is an in-memory read-only filesystem that mounts itself to a target and creates two files file001 and file002 that can only be read.
This project works on macOS,Linux and BSD systems.

**Compilation instructions on Linux Based targets :-**

**1.**  Make sure FUSE libraries are installed.  
For Ubuntu/Debian based systems :-  
`sudo apt-get install fuse libfuse-dev`

For RHEL/Fedora/CentOS:-  
`sudo yum install fuse fuse-devel`

**2.**  Run the following command  
`gcc simf.c -o simf 'pkg-config fuse --cflags --libs'`

**Running the project**  

Navigate to the directory containing `simf` executable and run the following commands:-   
**1.** `chmod 744 simf` *to make `simf`executeable.*

**2.** `./simf -f [mount_point]`
