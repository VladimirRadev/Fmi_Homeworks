#include <stdint.h>
#include <err.h>
#include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

typedef struct __attribute__((packed)) {
	uint16_t off;
	uint8_t b1;
	uint8_t b2;
} res;

int main (const int argc, const char* argv[])
{

	res s;
	int f1=open(argv[1],O_RDONLY);
	if(f1==-1)
	{
		err(1,"couldn't open file: %s\n",argv[1]);
	}

	int f2=open(argv[2],O_RDONLY);
	if(f2==-1)
	{
		err(1,"couldn't open file : %s\n",argv[2]);
	}

	int f3=open(argv[3],O_RDWR | O_CREAT | O_TRUNC,0642);
	
	if(f3==-1)
	{
		err(1,"couldn't open(create) file for writing: %s \n",argv[3]);
	}

	struct stat statFile1,statFile2;
	stat(argv[1],&statFile1);
	stat(argv[2],&statFile2);
    //printf("%ld %ld\n",statFile1.st_size,statFile2.st_size);
	if(statFile1.st_size != statFile2.st_size)
	{
		err(1,"The files' sizes don't match!\n");
	}
	for(s.off=0;s.off<statFile1.st_size;s.off++)
	{
		
		if(read(f1,&s.b1,sizeof(s.b1))==-1)
		{
			err(1,"Couldn't read data from file: %s\n",argv[1]);
		}
		
		if(read(f2,&s.b2,sizeof(s.b2))==-1)
		{
			err(1,"Couldn't read data from file: %s\n",argv[2]);
		}

		if(s.b1!=s.b2)
		{
			
			if(write(f3,&s,sizeof(s))==-1)
			{
				err(1,"Couldn't write triplet result into file: %s\n",argv[3]);
			}

		}

	}
	close(f1);
	close(f2);
	close(f3);

}

