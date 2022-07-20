#include <err.h>
#include <stdint.h>
#include <stdio.h>
       #include <sys/stat.h>
 #include <unistd.h>
    #include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>

typedef struct __attribute__((packed)) header{
	uint32_t magic;
	uint8_t header_version;
	uint8_t data_version;
	uint16_t count;
	uint32_t reserved1;
	uint32_t reserved2;
} header_t;

typedef struct __attribute__((packed)) version{
	uint16_t offset;
	uint8_t orgByte;
	uint8_t newByte;
} version0_t;

typedef struct __attribute__((packed)) version1{
	uint32_t offset;
	uint16_t orgword;
	uint16_t newword;

} version1_t;




int main(const int argc, const char* argv[])

{

	//1 patch.bin 2 f1.bin 3 f2.bin
	//
	//
	//
	//printf("%ld\n",sizeof(header_t));
	if(argc!=4)
	{
		err(1,"wrong input\n");
	}
	struct stat st;
	stat(argv[1],&st);
	if(!(st.st_size>=16 && ((st.st_size - 16) % 2 == 0 || (st.st_size - 16) % 1 == 0 )))
	{
		errx(1,"wrong patch.bin size \n");
	}
	

	int fdP=open(argv[1],O_RDONLY);
	int fdf1=open(argv[2],O_RDONLY);
	int fdf2=open(argv[3],O_RDWR | O_CREAT | O_TRUNC, 0644);
	if(fdP==-1)
	{
		err(1,"couldn't open patch\n");
	}
		if(fdf1==-1)
	{
		err(1,"couldn't open f1\n");
	}
			if(fdf2==-1)
	{
		err(1,"couldn't open f2\n");
	}






	header_t header;
	version0_t vs0;
	version1_t vs1;

	if(read(fdP,&header,sizeof(header))!=sizeof(header))
	{
		err(1,"couldn't read header");
	}
	if(header.magic!=0xEFBEADDE)
	{
		err(1,"wrogn magic");
	}
	if(header.header_version!=0x01)
	{
		err(1,"wrong header version");
	}

	if(header.data_version==0x00)
	{
		uint8_t byte;
		int rd=0,wr=0;
		while((rd=read(fdf1,&byte,sizeof(byte)))==sizeof(byte))
		{
			wr=write(fdf2,&byte,sizeof(byte));
			if(wr==0 || wr==-1)
			{
				err(1,"couldn't write byte");
			}

			
		}
		if(rd==-1)
			{
			err(1,"couldn't read from f1");	
			}
		
		while((rd=read(fdP,&vs0,sizeof(vs0)))==sizeof(vs0))
		{
			if(lseek(fdf2,vs0.offset * sizeof(vs0.orgByte),SEEK_SET)==-1)
			{
				err(1,"lseel seek set fd2 at vs 0");
			}
			wr=write(fdf2,&vs0.newByte,sizeof(vs0.newByte));
			if(wr==0 || wr==-1)
			{
				err(1,"couldn't write in fd2");
			}

		}
		if(rd==-1)
		{
			err(1,"couldn't read instruction from patch");
		}



	}
	else if(header.data_version==0x01)
	{
			uint8_t byte;
		int rd=0,wr=0;
		while((rd=read(fdf1,&byte,sizeof(byte)))==sizeof(byte))
		{
			wr=write(fdf2,&byte,sizeof(byte));
			if(wr==0 || wr==-1)
			{
				err(1,"couldn't write byte");
			}

			
		}
		if(rd==-1)
			{
			err(1,"couldn't read from f1");	
			}

	while((rd=read(fdP,&vs1,sizeof(vs1)))==sizeof(vs1))
		{
			if(lseek(fdf2,vs1.offset * sizeof(vs1.orgword),SEEK_SET)==-1)
			{
				err(1,"lseel seek set fd2 at vs 1");
			}
			wr=write(fdf2,&vs1.newword,sizeof(vs1.newword));
			if(wr==0 || wr==-1)
			{
				err(1,"couldn't write in fd2");
			}

		}
		if(rd==-1)
		{
			err(1,"couldn't read instruction from patch");
		}

	}
	else
	{
		err(1,"wrong data_version ");
	}
	close(fdP);
	close(fdf1);
	close(fdf2);








}

