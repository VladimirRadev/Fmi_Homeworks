#include <err.h>
#include <stdio.h>
#include <stdlib.h>
 #include <sys/stat.h>
       #include <fcntl.h>

 #include <unistd.h>
#include <sys/wait.h>
#include <stdint.h>
int main ( const int argc, const char* argv[])
{
	if(argc!=3)
	{
		err(1,"Argument count must be 3\n");
	}
	int fdO=open(argv[2],O_RDWR | O_CREAT | O_TRUNC, S_IWUSR | S_IRUSR);
	if(fdO==-1)
	{
		err(1,"couldn't open file %s\n",argv[2]);
	}
	int pipe_arr[2];
	if(pipe(pipe_arr)==-1)
	{
		err(1,"couldn't pipe file");
	}

	const pid_t fork_status=fork();
	if(fork_status==-1)
	{
		err(1,"couldn't fork the process\n");
	}
	if(fork_status==0)
		{
			//child
			close(pipe_arr[0]);
			if(dup2(pipe_arr[1],1)==-1)
			{
				err(1,"couldn't dup\n");
			}
			if(execlp("cat","cat",argv[1],(char*)NULL)==-1)
			{
				err(1,"couldn't exec");
			}
		}
	else
	{
		//parent
		int status;
		wait(&status);
		close(pipe_arr[1]);
		uint8_t readByte;
		int rd;
		uint8_t escapeChar=0x7D, artificialChar=0x55;
		while((rd=read(pipe_arr[0],&readByte,sizeof(readByte))) == sizeof(readByte))
		{
			if(readByte==0x00 || readByte==0xFF || readByte==0x55 || readByte==0x7D)
			{
				uint8_t aftXor=readByte ^ 0x20;
				if(write(fdO,&escapeChar,sizeof(escapeChar))==-1)
				{
					err(1,"couldn't write escape char in file");
				}
				if(write(fdO,&aftXor,sizeof(aftXor))==-1)
				{
					err(1,"couldn't write aftXor char in file");
				}				
			}
			else
			{
				if(write(fdO,&artificialChar,sizeof(artificialChar))==-1)
				{
					err(1,"couldn't write artificialChar in file");
				}
			}

		}
		if(rd==-1)
		{
			err(1,"couldn't read a byte\n");
		}


	}

	close(fdO);


}

