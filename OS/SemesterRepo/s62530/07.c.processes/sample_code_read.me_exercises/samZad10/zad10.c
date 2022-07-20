#include <err.h>
#include <stdio.h>
#include <stdlib.h>
       #include <sys/types.h>
       #include <unistd.h>

#include <unistd.h>
  #include <sys/types.h>
       #include <sys/wait.h>

int main ( const int argc, const char* argv[])
{
	if(argc!=3)
	{
		err(1,"2 commands must be providen");
	}

	const pid_t pid=fork();
	if(pid==-1)
	{
		err(1,"Couldn't fork");
	}
	if(pid==0)
	{
		//child
		if(execlp(argv[1],argv[1],(char*)NULL)==-1)
		{
			err(1,"Couldn't exec argument 1 %s\n",argv[1]);
		}

	}
	else
	{
		//parent
		int status;
		if(wait(&status)==-1)
		{
			err(1,"couldn't wait for child process to finish");
		}

		if(WEXITSTATUS(status)==0)
		{
			if(execlp(argv[2],argv[2],(char*)NULL)==-1)
			{
				//exit(42);
				err(42,"Couldn't exec argmuent 2 %s\n",argv[2]);
			}

		}


	}








}


