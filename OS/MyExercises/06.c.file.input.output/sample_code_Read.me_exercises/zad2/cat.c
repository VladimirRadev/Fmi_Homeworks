#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <err.h>



int main(const int argc , const char* argv[])
{
	if(argc == 1)
	{
		errx(1,"No arguments given");
	}

	char c[4096];
	int read_size=0,write_size=0;
	for (int i=1;i<argc;i++)
	{
		read_size=0;
		write_size=0;
		int fd=open(argv[i],O_RDONLY);
		if(fd==-1)
		{
			err(1,"Couldn't open file %s \n",argv[i]);
		}

		while((read_size=read(fd,&c,sizeof(c))) > 0)
		{
			write_size=write(1,&c,read_size);
			if(write_size==-1)
			{
				err(1,"Couldn't write file %s \n",argv[i]);
			}
		}
		if(read_size==-1)
		{
			err(1,"Couldn't read file %s \n",argv[i]);
		}
		close(fd);

	}

}

