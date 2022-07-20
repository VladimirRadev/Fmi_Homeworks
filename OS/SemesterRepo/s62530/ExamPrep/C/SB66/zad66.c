#include <stdint.h>
#include <err.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>

int pow_func(int base,int pow);
bool calcBit(uint16_t num,int idx);
int pow_func(int base,int pow)
{
	int result=1;
	for(int i=1;i<=pow;i++)
	{
		result*=base;
	}
	return result;
}

bool calcBit(uint16_t num, int idx)
{
	return (num/pow_func(2,idx)) % 2 ;
}

int main(const int argc, const char* argv[])
{
	if(argc!=3)
	{
		errx(1,"Program must take 2 argments in this format <input.bin> <output.bin>");
	}

	int fdInp=open(argv[1],O_RDONLY);
	if(fdInp==-1)
	{
		err(2,"Couldn't open input file: %s",argv[1]);
	}

	struct stat input_stat;
	if(stat(argv[1],&input_stat)==-1)
	{
		err(3,"Couldn't stat input file");
	}

	//input file must contain uint16_t nums ( 16 bits) 
	if(input_stat.st_size % 2 != 0)
	{	
		errx(4,"Input file wasn't in right format ( file's size must devide 2 without reminder");
	}

	int fdOut=open(argv[2],O_WRONLY | O_CREAT | O_TRUNC , S_IWUSR | S_IRUSR);
	if(fdOut==-1)
	{
		err(5,"Couldn't open and create output file %s",argv[2]);
	}

	bool bits[16];
	if(memset(bits,false,16*sizeof(bool))==NULL)
	{
		err(7,"Couldn't initialize bits arr with default values");
	}
	int rd=0,cnt=0;
	uint16_t cur=0;
	while((rd=read(fdInp,&cur,sizeof(uint16_t)))==sizeof(uint16_t))
	{
		//dprintf(1,"%d\n",cur);	
		for(int i=15;i>=0;i--)
		{
			bits[cnt++]=calcBit(cur,i);
		}
		uint8_t out=0;
		for(int i=0;i<=15;i+=2)
		{
			//10 -> 1 in output file
			if(bits[i]==true && bits[i+1]==false)
			{
				//imitating binary num to decimal num translation
			
				out+=1*pow_func(2,7-(i/2));
			
				
				//	dprintf(1,"loop %d\n",out);
			}
			//01 -> 0 in output file
			else if(bits[i]==false && bits[i+1]==true)
			{
				//imitating binary num to decimal num translation
				out+=0*pow_func(2,7-(i/2));
			
				
				
				
				
				//	dprintf(1,"loop %d\n",out);

			}
			else
			{
				warnx("Input file  %s contains byte where 00 or 11 are consecutive . Nothing was decoded at this iteration ",argv[1]);
				break;
			}
		}
		//dprintf(1,"%d\n",out);
		if(write(fdOut,&out,sizeof(out))!=sizeof(out))
		{
			err(3,"Couldn't write output num into output file %s", argv[2]);
		}
		cnt=0;
	}
	if(rd==-1)
	{
		err(6,"Couldn't read 2 bytes from inputfile: %s " ,argv[1]);
	}




	close(fdInp);
	close(fdOut);

}

