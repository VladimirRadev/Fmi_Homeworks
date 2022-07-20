#include <err.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
   #include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>
 #include <unistd.h>
    #include <sys/types.h>
       #include <unistd.h>
       #include <unistd.h>
#include <unistd.h>
#include <stdlib.h>
typedef struct __attribute__((packed))
{
	char fileName[8];
	uint32_t offset;
	uint32_t length;

} triple_t;
int main(const int argc, const char* argv[])
{
	if (argc!=2)
	{
		errx(1,"Program must take an argument in this format: ./main <filename>");
	}

	int fdInput=open(argv[1],O_RDONLY);
	if(fdInput==-1)
	{
		err(2,"Program couldn't open the input file %s " ,argv[1]);
	}

	struct stat fdInput_stat;

	if(stat(argv[1],&fdInput_stat)==-1)
	{
		err(3,"COulnd't stat input file");
	}
	triple_t triple;
	if( !(fdInput_stat.st_size % sizeof(triple) == 0 && (fdInput_stat.st_size / sizeof(triple)) <= 8))
	{
		err(4,"Input file corupted ( not valid format or larger than 8 triples)");
	}

	uint8_t triplesCount=fdInput_stat.st_size / sizeof(triple);

	int pipe_fds[8][2];

	for(uint8_t i=0;i<triplesCount;i++)
	{
			if(pipe(pipe_fds[i])==-1)
			{
				err(5,"Error while creating pipes");
			}
	}

	for(uint8_t i=0;i<triplesCount;i++)
	{
		if(read(fdInput,&triple,sizeof(triple))!=sizeof(triple))
		{
			err(4,"couldn't read triple");
		}
		pid_t child=fork();
		if(child==-1)
		{
			err(6,"Couldn't fork process");
		}
		if(child==0)
		{
			//writes

			close(pipe_fds[i][0]);

			int fd=open(triple.fileName,O_RDONLY);
			if(fd==-1)
			{
				err(5,"couldn't open triple filename for reading");
			}
			lseek(fd,triple.offset * sizeof(uint16_t),SEEK_SET);

			uint16_t res=0x0000;

			for(uint32_t j=0;j<triple.length;j++)
			{
				uint16_t cur=0;
				read(fd,&cur,sizeof(cur));
				res^=cur;
			}

			close(fd);
			write(pipe_fds[i][1],&res,sizeof(res));
			exit(0);
		}
		else if( child > 0)
		{
			//reads
			close(pipe_fds[i][1]);
		}
	}


	uint16_t global=0;

	for(uint8_t i=0;i<triplesCount;i++)
	{
		uint16_t tripleRes=0;
		read(pipe_fds[i][0],&tripleRes,sizeof(tripleRes));

		global^=tripleRes;
	}


	dprintf(1,"result: %x\n",global);





}

