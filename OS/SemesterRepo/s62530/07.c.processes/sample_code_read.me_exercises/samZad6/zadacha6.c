 #include <stdio.h>
#include <err.h>
#include <sys/wait.h>
 #include <sys/types.h>
       #include <unistd.h>
#include <stdlib.h>
  #include <unistd.h>

int main(const int argc, const char* argv[])
{
	if(argc!=2)
	{
		errx(1,"The program has to take an argument\n");
	}

	pid_t a =fork();
	int status;
	if(a==-1)
	{
		err(1,"Boo\n");
	}
	if(a==0)
	{

		if(execlp(argv[1],(char *) NULL )==-1)
		{
			err(1,"Exec error");
		}
		exit(0);

	}
	else
	{
		wait(&status);
		if(status==0)
		{
			printf("succsed\n");
		}

	}



}

