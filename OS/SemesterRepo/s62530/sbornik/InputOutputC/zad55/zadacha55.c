#include <err.h>
#include <stdio.h>
#include <stdint.h>
 #include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>
#include <unistd.h>

typedef struct __attribute__(( packed ))  triplet
{
	uint16_t off;
	uint8_t org;
	uint8_t rep;
} triplet_t;

int main (const int argc, const char * argv[])
{	
	if(argc!=4)
	{
		err(1,"program must take 3 arguments\n");
	}
	int fd1=open(argv[1],O_RDONLY);
	if(fd1==-1)
	{
		err(1,"Program cannot open file: %s\n",argv[1]);
	}
	int fd2=open(argv[2],O_RDONLY);
	if(fd2==-1)
	{
		err(1,"Program cannot open file: %s\n",argv[2]);
	}
	int fd3=open(argv[3],O_RDWR | O_CREAT|O_TRUNC, S_IRUSR | S_IWUSR);
	if(fd3==-1)
	{
		err(1,"Program cannot open(create) file: %s\n",argv[3]);
	}

	triplet_t res;
	struct stat patchStat;
	fstat(fd3,&patchStat);
	if(patchStat.st_size % sizeof(res) != 0 )
	{
		err(1,"Patch file size doesn't devide triplet size without remainder \n");
	}
	char c;
	int rd=0,wr=0;
	while ( (rd=read(fd2,&c,sizeof(c))) == sizeof(c))
	{
		wr=write(fd3,&c,sizeof(c));
		if(wr==-1)
			{
				err(1,"writing\n");
			}
	}
	if(rd==-1)
	{
		err(1,"reading\n");
	}

	lseek(fd3,0,SEEK_SET);


	while((rd=read(fd1,&res,sizeof(res))) == sizeof(res))
	{
		lseek(fd3,res.off*sizeof(uint8_t),SEEK_SET);
		uint8_t h;
		if(read(fd3,&h,sizeof(uint8_t))==-1)
		{
			err(1,"reading h \n");
		}
		if(h!=res.org)
		{
			err(1,"Patch.bin contains wrong information about byte: %d at position %d\n",h,res.off);
		}
		lseek(fd3,-1,SEEK_CUR);
		if(write(fd3,&res.rep,sizeof(res.rep))==-1)
		{
			err(1,"Replacing a byte in f2.bin with new taken from patch.bin's triplet\n");
		}



	}
	if(rd==-1)
	{
		err(1,"reading from patch.bin\n");
	}

	close(fd1);
	close(fd2);
	close(fd3);












}

