#include <stdint.h>
#include <err.h>
  #include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>
  #include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>
   #include <unistd.h>
  #include <sys/types.h>
       #include <unistd.h>
#include <stdio.h>

int main(const int argc,const char* argv[])
{


	if(argc!=3)
	{
		err(2,"2 argmuients must be provided");
	}

	int fd[2];
	pipe(fd);

	const pid_t pid=fork();
	if(pid==-1)
	{

	err(1,"er");
	}
	//
	if(pid==0)
	{
		//writes
		//
		close(fd[0]);
		dup2(fd[1],1);

		if(execlp("cat","cat",argv[1],(char*)NULL)==-1)
		{
			err(2,"ks");
		}
	}

	//reads
	//
	close(fd[1]);

	int fdOut=open(argv[2],O_WRONLY | O_CREAT | O_TRUNC , S_IRUSR | S_IWUSR);
	if(fdOut==-1)

	{
		err(2,"couldn't create and open %s",argv[2]);
	}

	uint8_t byte;
	int rd=0;
	while((rd=read(fd[0],&byte,sizeof(uint8_t))) > 0)
	{
		if(byte==0x7d)
		{
			if(read(fd[0],&byte,sizeof(uint8_t))!=sizeof(uint8_t))
			{
				err(2,"Reading error");
			}

			byte=byte ^ 0x20;

			if(write(fdOut,&byte,sizeof(byte))!=sizeof(uint8_t))
			{
				err(2,"Writing error");
			}

		}	
		else if (byte == 0x55)
		{
			continue;
		}	
	}
	if(rd==-1)
	{
		err(2,"coudnt' read from %s file ",argv[1]);
	}


	close(fdOut);



}

