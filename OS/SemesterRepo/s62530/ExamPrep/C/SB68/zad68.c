#include <unistd.h>
#include<stdint.h>
#include <err.h>
  #include <sys/types.h>
       #include <unistd.h>
 #include <unistd.h>

int main (const int argc, const char* argv[])
{
	if(argc!=2)
	{
		errx(1,"Program must take an argument : filename for sorting");
	}
	
	int pipe_fd[2];
	if(pipe(pipe_fd)==-1)
	{
		err(2,"Couldn't create pipe");
	}

	const pid_t child=fork();
	
	//child
	if(child==0)
	{
		//write
		
		close(pipe_fd[0]);
		if(dup2(pipe_fd[1],1)==-1)
		{
			err(3,"couldn't dup2 pipe_fd[1] to 1 ");
		}
		if(execlp("cat","cat", argv[1],(char*)NULL)==-1)
		{
			err(4,"Couldn't exec cat command on file: %s",argv[1]);
		}
	
	}
	//parent
	else if(child > 0)
	{
		//read
		close(pipe_fd[1]);
		
		if(dup2(pipe_fd[0],0)==-1)
		{
			err(5,"couldn't dup2 pipe_fd[0] to 0");
		}

		if(execlp("sort","sort",(char*)NULL)==-1)
		{
			err(6,"Couldn't exec sort command");
		}
	}

	else
	{
		err(3,"Program couldn't fork the process");
	}



}
