#include <err.h>
#include <string.h>
#include <stdio.h>
   #include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>
  #include <unistd.h>
 #include <stdlib.h>


int sizeOfStr(const char* str)
{
	int size=0;
	while(str[size]!='\0')
	{
		size++;
	}
	return size;
}


int main(const int argc , const char* argv[])
{
	if(argc <= 3)
	{
		errx(1,"No enough arguments given");
	}



	//argv[argc-1]

	char c[4096];
	int read_size=0,write_size=0,dirLength=sizeOfStr(argv[argc-1]);
	
	for(int i=1;i<argc-1;i++)
	{
		int fd=open(argv[i],O_RDONLY);
		if(fd==-1)
		{
			err(1,"Couldn't open file %s\n",argv[i]);
		
		}
			int sizeofFile=sizeOfStr(argv[i]);
			char* path=malloc(sizeofFile+dirLength+3);
			strcat(path,argv[argc-1]);	
			path[strlen(argv[argc-1])]='/';	
		   	strcat(path,argv[i]);		
			int destFd=open(path,O_RDWR|O_TRUNC|O_CREAT,0644);
			if(destFd==-1)
			{
				free(path);
				err(1,"wrong dir name %s\n",argv[argc-1]);
			}

		while((read_size=read(fd,&c,sizeof(c))) > 0)
		{	
			write_size=write(destFd,&c,read_size);
			if(write_size==-1)
			{
				free(path);
				err(1,"Couldn't write in %s\n",path);
			}
					
		}

		if(read_size==-1)
		{	
			free(path);
			err(1,"Couldn't read file %s\n",argv[i]);
		}
		free(path);
		close(destFd);
		close(fd);

	}


}

