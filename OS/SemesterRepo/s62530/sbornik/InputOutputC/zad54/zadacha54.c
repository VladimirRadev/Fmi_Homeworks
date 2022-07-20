#include <err.h>
#include <unistd.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
     #include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>

int main(const int argc , const char* argv[])
{        	
	if ( argc < 2)
	{
		char c='\0';
		int read_size=0,write_size=0;
		while((read_size=read(0,&c,sizeof(c))) > 0)
		{	
			write_size=write(1,&c,read_size);
			if(write_size==-1)
			{
				err(1,"Program couldn't write a char to stdout \n");
			}
		}
		if(read_size==-1)
		{
			err(1,"Program couldn't read data from stdin \n");
		}


	}

	else if(strcmp(argv[1],"-n")==0)
	{
		//-n and stdin
		if(argc==2)
		{
			int lineCount=1;
			char c='\0';
			char* arr=malloc(5000);
		int read_size=0,index=0;
		while((read_size=read(0,&c,sizeof(c))) > 0)
		{	
			if(c=='\n')
			{
				printf("%d %s\n",lineCount,arr);
				memset(arr,0,index+1);
				index=0;
				lineCount++;
				continue;
			}
			arr[index++]=c;

			
		}
		if(read_size==-1)
		{
			err(1,"Program couldn't read data from stdin \n");
		}
		free(arr);
		}


		//-n and files or stdin
		else
		{
		int lineCount=1;
		for(int i=2;i<argc;i++)
		{
			if(strcmp(argv[i],"-")==0)
			{
					char c='\0';
			char* arr=malloc(5000);
		int read_size=0,index=0;
		while((read_size=read(0,&c,sizeof(c))) > 0)
		{	
			if(c=='\n')
			{
				printf("%d %s\n",lineCount,arr);
				memset(arr,0,index+1);
				index=0;
				lineCount++;
				continue;
			}
			arr[index++]=c;

			
		}
		if(read_size==-1)
		{
			err(1,"Program couldn't read data from stdin \n");
		}
		free(arr);
			}
       //nekuv file
			else
			{
					char c='\0';
			char* arr=malloc(5000);
		int read_size=0,index=0;
		int fd=open(argv[i],O_RDONLY);
		if(fd==-1)
			{
				err(1,"couldn't open argument file: %s",argv[i]);
			}


		while((read_size=read(fd,&c,sizeof(c))) > 0)
		{	
			if(c=='\n')
			{
				printf("%d %s\n",lineCount,arr);
				memset(arr,0,index+1);
				index=0;
				lineCount++;
				continue;
			}
			arr[index++]=c;

			
		}
		if(read_size==-1)
		{
			err(1,"Program couldn't read data from file: %s \n",argv[i]);
		}
		free(arr);
		close(fd);
			}

		}

		}

		
	}
	//!-n but files >=1
	else
	{
			//stdin or file
		for(int i=1;i<argc;i++)
		{
			if(strcmp(argv[i],"-")==0)
			{
					char c='\0';
			char* arr=malloc(5000);
		int read_size=0,index=0;
		while((read_size=read(0,&c,sizeof(c))) > 0)
		{	
			if(c=='\n')
			{
				printf("%s\n",arr);
				memset(arr,'\0',index+1);
				index=0;
				continue;
			}
			arr[index++]=c;

			
		}
		if(read_size==-1)
		{
			err(1,"Program couldn't read data from stdin \n");
		}
		free(arr);
			}
       //nekuv file
			else
	{
					char c='\0';
			char* arr=malloc(5000);
		int read_size=0,index=0;
		int fd=open(argv[i],O_RDONLY);
		if(fd==-1)
		{
			
				err(1,"couldn't open argument file: %s",argv[i]);
		}


		while((read_size=read(fd,&c,sizeof(c))) > 0)
		{	
			if(c=='\n')
			{
				printf("%s\n",arr);
				memset(arr,0,index+1);
				index=0;
				continue;
			}
			arr[index++]=c;

			
		}
		if(read_size==-1)
		{
			err(1,"Program couldn't read data from file: %s \n",argv[i]);
		}
		free(arr);
		close(fd);

			}
		}
	}

}

