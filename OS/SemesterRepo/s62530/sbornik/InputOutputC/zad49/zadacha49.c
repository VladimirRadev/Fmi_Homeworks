#include <err.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(const int argc, const char* argv[])
{
	if(argc != 2)
	{
		err(1,"Program should take only an argument - binary file name\n");
	}
	int fdArg=open(argv[argc-1],O_RDWR);
	if(fdArg==-1)
	{
		err(1,"Program couldn't open the binary file for writing and reading\n");
	}

	uint8_t cur=0;
	int countingArr[256]={0};
   	int read_size=0;
	while((read_size=read(fdArg,&cur,sizeof(cur)))==sizeof(uint8_t))
	{
		countingArr[cur]++;
	}
	if(read_size==-1)
	{
		err(1,"Couldn't read data from binary file\n");
	}

	lseek(fdArg,0,SEEK_SET);
	int write_size=0;
	for(int i=0;i<256;i++)
	{
		if(countingArr[i]>0)
		{
			for(int j=0;j<countingArr[i];j++)
			{
				write_size=write(fdArg,&i,sizeof(uint8_t));
				if(write_size==-1)
				{
					err(1,"Couldn't write data in binary file\n");
				}

			}
		}
	}
	close(fdArg);




}

