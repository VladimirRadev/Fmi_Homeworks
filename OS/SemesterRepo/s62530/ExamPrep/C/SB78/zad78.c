#include <stdint.h>
#include <stdio.h>
#include <err.h>
#include <string.h>
     #include <sys/types.h>
       #include <sys/wait.h>

      #include <unistd.h>
#include <stdlib.h>

int main(const int argc, const char*  argv[])
{
	if(argc!=3)
	{
		errx(1,"Program must take two digits N and D");
	}

	if(strlen(argv[1])> 1 || strlen(argv[2]) > 1)
	{
		errx(2,"Program must take digits");
	}

	char n,d;
	n=argv[1][0];
	d=argv[2][0];

	int N=(int)(n - '0');
	int D=(int)(d - '0');

	for(int i=0;i<N;i++)
	{
//		dprintf(1,"sex %d\n",i);


		int pipe_fd[2];
		if(pipe(pipe_fd)==-1)
		{
			err(3,"couldn't pipe");
		}

		pid_t child=fork();
		if(child==-1)
		{
			err(1,"Couldn't fork");
		}

		//child
		if(child==0)
			{
				//reads
				pid_t waitStatus;
				close(pipe_fd[1]);
					
				read(pipe_fd[0],&waitStatus,sizeof(pid_t));
				dprintf(1,"DONG\n");
				exit(0);
			}
		//parent
		else if(child > 0)
			{
				//writes
				close(pipe_fd[0]);
				
				dprintf(1,"DING\n");
				
				pid_t my_pid=getpid();

				write(pipe_fd[1],&my_pid,sizeof(pid_t));
			
				wait(NULL);

				sleep(D);
			}
	}

}
