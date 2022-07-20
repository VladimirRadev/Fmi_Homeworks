#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <err.h>
#include <unistd.h>
int main(const int argc, char* argv[])
{
	int fd1=open(argv[1],O_RDONLY);
	if ( fd1 == -1 )
	{
		err(2,"could open file1");
	}

	int fd2=open(argv[2],O_CREAT | O_RDWR | O_TRUNC , 0644);
	
	char c='\0';
	int n=0;
	while((n=read(fd1,&c,1)) > 0)
	{
		write(fd2,&c,1);
	}

	close(fd1);
	close(fd2);

}

