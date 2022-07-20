#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <err.h>

int powfunc(int base,int pow);
bool bitCalc(uint8_t byte,int idx);

int powfunc(int base,int pow)
{
	int res=1;
	for(int i=1;i<=pow;i++)
	{
		res*=base;
	}
	return res;
}

bool bitCalc(uint8_t byte,int idx)
{	
	// return (byte/powfunc(2,idx))%2;
	return (((byte >> idx) & 1) == 1);
}

int main(const int argc, const char* argv[])
{
	if (argc != 4) {
		errx(1, "expected 3 argument but got %d arguments", argc - 1);
	}

	int fdScl=open(argv[1],O_RDONLY);
	if(fdScl==-1)
	{
		err(1,"Couldn't open scl file");
	}
	int fdSdl=open(argv[2],O_RDONLY);
   	if(fdSdl==-1)
	{
		err(1,"Couldn't open sdl file");
	}
	int fdOutput=open(argv[3],O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if(fdOutput==-1)
	{
		err(1,"couldn't create output file\n");
	}


	uint8_t byte;
	int rd=0;
	while((rd=read(fdScl,&byte,sizeof(byte)))==sizeof(byte))
	{
		uint16_t temp=0;
		for(int i=7;i>=0;i--)
		{	
			if(read(fdSdl,&temp,sizeof(temp)) == -1)
			{
				err(1,"couldn't read from sdl file");
			}	

			if (bitCalc(byte,i)) {
				if(write(fdOutput,&temp,sizeof(temp))==-1)
				{
					err(1,"couldn't write in output file");
				}
			}
		}
	}
	if(rd==-1)
	{
		err(1,"couldn't read from scl file");
	}

	close(fdScl);
	close(fdSdl);
	close(fdOutput);
}

