#include <stdio.h>
#include <err.h>
#include <stdlib.h>
  #include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>
  #include <unistd.h>
#include <string.h>
 #include <sys/types.h>
       #include <sys/wait.h>


int main()
{	
	int fd=open("./doo",O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if(fd==-1)
	{
		err(1,"couldn't open file");
	}
	const char * fooStr="foo\n";
	const char * barStr="bar\n";

	const pid_t pid=fork();
	if(pid==-1)
	{
		err(1,"couldn't fork");
	}
	if(pid==0)
	{
		//child
		
		if(write(fd,fooStr,strlen(fooStr))==-1)
		{

			err(1,"no writing foo" );
		}
		
		close(fd);
		exit(0);
	
	}
	else
	{
		wait(NULL);
		if(write(fd,barStr,strlen(barStr))==-1)
		{
			err(1,"no writing bar");
		}


	}
	close(fd);






}

