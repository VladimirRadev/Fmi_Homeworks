#include <err.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
 #include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>
#include <unistd.h>
 #include <sys/types.h>
       #include <sys/wait.h>
#include <stdio.h>


int main (const int argc, const char* argv[])
{
	if(argc!=2)
	{
		err(1,"Program must take an argument: name of file\n");
	}

	const char* str="foobar";
	int fd=open(argv[1],O_RDWR | O_CREAT | O_TRUNC , S_IWUSR | S_IRUSR);
	if(fd==-1)
	{
		err(1,"Couldn't open the file");
	}

	const pid_t pid=fork();
	if(pid==-1)
	{
		err(1,"couldn't fork");
	}

	if(pid==0)
	{
		//child
		if(write(fd,str,strlen(str))==-1)
		{
			err(1,"couldn't write in file");
		}
		close(fd);
		exit(0);

	}
	else
	{
		//parent
		
		int status;
		wait(&status);
		if(status==-1)
		{
			err(1,"error while waiting child process to finish");
		}
		//printf("%d\n",status);
	    if(status==0)
		{
			char c[2];
			int rd=0;
			lseek(fd,0,SEEK_SET);
			while((rd=read(fd,c,2))==2)
			{
				char space=' ';
				if(write(1,c,2)==-1)
				{
					err(1,"couldn't write 2 chars");
				}
				if(write(1,&space,1)==-1)
				{
					err(1,"couldn't write a space");
				}

			}

    //		printf("%d\n",rd);
			if(rd==-1)
			{
				err(1,"couldn't read");
			}



		}

	}

	close(fd);





}

