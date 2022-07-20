#include <stdint.h>
       #include <sys/types.h>
       #include <unistd.h>
 #include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>
       #include <unistd.h>
#include <err.h>
#include <stdio.h>

typedef struct __attribute__((packed))
{
	char arr[4];
	uint16_t count;
	char arr1[10];
} header_t;
typedef struct __attribute__((packed))
{
	uint16_t off;
	uint16_t length;
} interval_t;

int main(const int argc,const char* argv[])
{
	if(argc!=7)
	{
		errx(1,"6 arguments are needed");
	}
	int sizes[4]={4,1,2,8};
	header_t header;
	interval_t k[4];
	int f[4];
	
	int fdAssix;
	if((fdAssix=open(argv[1],O_RDONLY))==-1)
	{
		err(1,"Error in opening assix file");
	}

	for(int i=2;i<argc-1;i++)
	{
		f[i-2]=open(argv[i],O_RDWR);
	}
	int fdCrusifix=open(argv[argc-1],O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if(fdCrusifix==-1)
	{
		err(1,"Error in opening fdCrusifix file");
	}
	uint8_t e[8];
	read(fdAssix,&header,sizeof(header_t));
	int rd=0;
	while((rd=read(fdAssix,k,16))==16)
	{
		for(int i=0;i<4;i++)
		{

	//	 fprintf(stdout,"%d %d %d \n",i,k[i].off,k[i].length);
		}
		for(int i=0;i<4;i++)
		{
			if(lseek(f[i],sizeof(header) + k[i].off * sizes[i],SEEK_SET)==-1)
			{
				err(1,"lseek");

			}

			for(int j=0;j<k[i].length;j++)
			{
			    
				if(read(f[i],e,sizes[i])!=sizes[i])
				{
					err(1,"error");
				}
			    //fprintf(stdout,"%d  %04lx\n",sizes[i],e);

				if(write(fdCrusifix,e,sizes[i])!=sizes[i])
				{
					err(1,"error");
				}
				

			}

		}

	}
	
	close(fdAssix);
	for(int i=0;i<4;i++)
	{
		close(f[i]);
	}
	close(fdCrusifix);





}
