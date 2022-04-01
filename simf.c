#define FUSE_USE_VERSION 30

#include <stdio.h>
#include <fuse.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>


//do_getattr is called when specific file attributes are needed by the system

static int do_getattr(const char *path, struct stat *st)
{

	printf("\nAttrs of %s requested\n",path);
	st-> st_uid = getuid(); //File Owner
	st-> st_gid = getgid(); //User Group of Owner
	st-> st_atime = time(NULL); //Last Access time of file
	st-> st_mtime = time(NULL); //Last Modification time of file
	if(strcmp(path , "/")== 0 ){
		/*
		 * st_mode specifies if file in question is a directory,
		 * regular file or other;
		 *
		 * st_nlink specifies number of hardlinks
		 *
		 * st_size is size of file in bytes
		 *
		 * S_IFDIR macro indicates file is a directory 
		 * we do a bitwise or to set default permission bits
		 * 	-rwx-r-x-r-x = 0755 (Why directory bit 0? because 0|1 = 1)
		 * no of hardlinks is set to 2 by default for directories
		 * 
		 * S_IFREG is used to indicate regular files
		 * we do a bitwise or to set permission bits as
		 * 	-rw-r--r-- = 0644
		 * no of hardlinks set to 1 by default for regular files
		 *
		 * st_size = 1024 bytes for files is set here
		 */
		
		//This block of code is executed for root directory of SIMF 
		st-> st_mode = S_IFDIR | 0755 ; 
		st-> st_nlink = 2;
	}
	else{
		//This block is executed for all files other than root directory
		st-> st_mode = S_IFREG | 0644 ;
		st-> st_nlink = 1;
		st-> st_size = 1024;
	}
	

	return 0;
}
static int do_readdir( const char *path, void *buffer, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi )
{
	/*
	 *We define the files available in the location in the do_readdir function it has five parameters:-
	 path = path of the directory in question;
	 buffer =  contains the names of files/directories 
which are available inside the directory in question.
	 filler is the function sent by fuse we could use it to fill the buffer with available files in path , the function returns 0 on success

	 * */
	printf("::::::::Listing Files:::::::::\npath:-%s\t\t::",path);
	filler(buffer,".",NULL,0);//Current Directory
	filler(buffer,"..",NULL,0);//Parent Directory

	if(strcmp(path,"/")==0){
		filler(buffer,"file001",NULL,0);
		filler(buffer,"file002",NULL,0);
	}	
	return 0;
}

//Implementing a read function

static int do_read(const char *path, char *buffer,size_t size, off_t offset, struct fuse_file_info *fi){
	/* 
	 * path = path of the file system wants to read
	 * buffer = chunk the system is interested in 
	 * size = size of this chunk
	 * offset = cursor position from where we want to read our file
	 *
	 * 
	 */
	char file001text[26] = "Hewwo There from file001"; //Content of file001
	file001text[25] = 04; //Manual EOF insertion
	char file002text[26] = "Hewwo World form file002"; //Content of file002
	file002text[25] = 04; //Manual EOF insertion
	char *selectedText = NULL;//pointer to hold file data later

	if(strcmp(path,"/file001")== 0 ){
		selectedText = file001text;
	}else if(strcmp(path , "/file002")== 0){
		selectedText = file002text;
	}else{
		return -1;
	}
	memcpy(buffer, selectedText + offset , size);

	return strlen(selectedText)-offset ;

}

static struct fuse_operations operations = {
	.getattr = do_getattr,
	.readdir = do_readdir,
	.read = do_read,
};

int main(int argc, char *argv[]){
	return fuse_main(argc, argv, &operations , NULL);
}

