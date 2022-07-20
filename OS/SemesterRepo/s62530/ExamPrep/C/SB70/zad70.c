 #include <sys/types.h>
       #include <sys/wait.h>
#include <err.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

int main()
{
	

	int p_fd[4][2];
	for(int i=0;i<4;++i)
	{
		if(pipe(p_fd[i])==-1)
		{
			err(1,"couldn' create pipe : %d",i);
		}
	}

	//cat -> cut
	//
	pid_t p=fork();

	if(p==-1)
	{
		err(3,"Couldn't fork cat->cut pipe");
	}

	///child
	if(p==0)
	{
	
		//..write
		close(p_fd[0][0]);

		if(dup2(p_fd[0][1],1)==-1)
		{
			err(4,"couldn't dup2 p_fd[0][1]");
		}
		if(execlp("cat","cat","/etc/passwd",(char*)NULL)==-1)
		{
			err(5,"couldn't exec cat command");
		}
	}
	//parent
	
	close(p_fd[0][1]);

	p=fork();

	if(p==-1)
	{
		err(3,"cut-> sort fork() problem");
	}
	if(p==0)
	{

		//..write cut -> sort
	close(p_fd[1][0]);

	
	if(dup2(p_fd[0][0],0)==-1)
	{
		err(6,"Couldn't dup2 p_fd[0][0]");
	}

	if(dup2(p_fd[1][1],1)==-1)
	{
		err(6,"Couldn't dup2 p_fd[1][1]");
	}

	if(execlp("cut", "cut" , "-d", ":", "-f", "7", (char*)NULL)==-1)
	{
		err(7,"Couldn't exec cut command");
	
	}
	}


	//parent
	//
	close(p_fd[1][1]);

	p=fork();

	if(p==-1)
	{
		err(5,"Couldn't fork for sort command");
	}

	if(p==0)
	{
		//read from p_fd[1][0] write p_fd[2][1]
		//
		//sort
		//
	
		close(p_fd[2][0]);

		if(dup2(p_fd[1][0],0)==-1)
		{
			err(6,"Couldn't dup2 p_fd[1][0]");
		}

		if(dup2(p_fd[2][1],1)==-1)
		{
			err(6,"Couldn't dup2 p_fd[2][1]");
		}

		if(execlp("sort","sort",(char*) NULL)==-1)
		{
			err(6,"Couldn't exec sort command");
		}
	}

	//parent
	//
	close(p_fd[2][1]);
	p=fork();

	if(p==-1)
	{
		err(4,"Couldn't fork () program near uniq");
	}
	//child
	if(p==0)
	{
		//reads from p_fd[2][0] and writes p_fd[3][1]
		//
		//uniq
		//
		
		close(p_fd[3][0]);
		
		if(dup2(p_fd[2][0],0)==-1)
		{
			err(4,"couldn't dup2 p_fd[2][0]");
		}
		if(dup2(p_fd[3][1],1)==-1)
		{
			err(5,"Couldn't dup2 p_fd[3][1]");
		}

		if(execlp("uniq","uniq","-c",(char*)NULL)==-1)
		{
			err(6,"Couldn't exec uniq command");
		}
	}

	//parent

	//reads 
	//sort
	close(p_fd[3][1]);

	if(dup2(p_fd[3][0],0)==-1)
	{
		err(6,"Couldn't dup2 p_fd[3][0]");
	}

	if(execlp("sort","sort","-n","-k","1",(char*)NULL)==-1)
	{
		err(5,"Coulldn't exec second sort ");
	}
	
}

