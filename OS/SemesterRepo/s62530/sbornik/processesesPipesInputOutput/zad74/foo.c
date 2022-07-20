   #include <sys/types.h>
       #include <sys/stat.h>
    #include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>
     #include <unistd.h>
#include <err.h>
#include <stdint.h>
#include <stdio.h>
int main(const int argc, const char* argv[])
{
	if(argc!=2)
	{
		err(1,"Program must take an argmunt: file name \n");
	}

	if(mkfifo("mkio",S_IWUSR | S_IRUSR)==-1)
	{
		err(1,"couldn't create the pipe\n");
	}
	int fd=open("mkio",O_WRONLY);
	if(fd==-1)
	{
		err(1,"couldn't open the file\n");
	}
	if(dup2(fd,1)==-1)
	{
		err(1,"couldn't write in the pipe\n");
	}
	if(execlp("cat","cat",argv[1],(char*)NULL)==-1)
	{
		close(fd);
		err(1,"couldn't exec cat\n");
	}
}

