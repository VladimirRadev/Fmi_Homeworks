
 #include <stdio.h>
#include <stdint.h>
 #include <sys/types.h>
       #include <sys/stat.h>
       #include <unistd.h>
   #include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>
 #include <unistd.h>
#include <err.h>
typedef struct __attribute__((packed))
{
	uint32_t x;
	uint32_t y;
}	pair_t;
int main(const int argc, const char* argv[])
{
	if (argc != 3)
	{
		errx(1,"2 arguments must be provided\n");
	}
	int fdf1=open(argv[1],O_RDONLY);
	if(fdf1==-1)
	{
		err(1,"Couldn't open f1 file\n");
	}
	int fdf2=open(argv[2],O_RDONLY);
	if(fdf2==-1)
	{
		err(1,"couldn't open f2 file \n");
	}
	int fdf3=open("f3",O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);
	if (fdf3==-1)
	{
		err(1,"couldn't create and open f3 file \n");
	}

	struct stat statF1,statF2;
	if(fstat(fdf1,&statF1)==-1)
	{
		err(1,"error while trying to stat f1 file\n");
	}
	if(fstat(fdf2,&statF2)==-1)
	{
		err(1,"error while trying to stat f2 file\n");
	}

	if(!(statF1.st_size % 8 ==0  && statF2.st_size % 4 == 0)) 
	{
		err(1,"File f1 and f2 with wrong bytes size ( f1 has to be devided by 8 and 4 and f2 has to be devided by 4 aswell)");
	}
	pair_t pair;
	int rd=0,wr=0;
	uint32_t outcome=0;

	while((rd=read(fdf1,&pair,sizeof(pair)))==sizeof(pair))
	{
		if(lseek(fdf2,pair.x * sizeof(uint32_t),SEEK_SET)==-1)
		{
			err(1,"lseek seek set error while tried to set at position x in f2 file\n");
		}
		int rdF3=0;
		for(uint32_t i=0;i<pair.y;i++)
		{
			if((rdF3=read(fdf2,&outcome,sizeof(outcome)))!= sizeof(outcome))
			{
				err(1,"couldn't read outcome num from f2 file\n");
			}
			if((wr=write(fdf3,&outcome,sizeof(outcome))) != sizeof(outcome))
			{
				err(1,"couldn't write outcome num in f3 file\n");
			}
		}
	}
	if(rd==-1)
	{
		err(1,"couldn't read pair from f1 file\n");
	}

	if(close(fdf1)==-1)
	{
		err(1,"couldn't close f1 file\n");
	}

	if(close(fdf2)==-1)
	{
		err(1,"couldn't close f2 file\n");
	}
	if(close(fdf3)==-1)
	{
		err(1,"couldn't close f3 file\n");
	}
}

