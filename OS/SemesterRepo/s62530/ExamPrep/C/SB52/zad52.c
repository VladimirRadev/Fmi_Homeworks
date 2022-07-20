  #include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
      #include <err.h>
#include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>
       #include <unistd.h>
     #include <sys/stat.h>

typedef struct __attribute__((packed))
{
	uint16_t offset;
	uint8_t length;
	uint8_t reserved;

} idx_triple_t;

int main(const int argc ,const char * argv[])
{
	/*uint8_t arr[1000];
	int fd=open("f1.dat",O_RDONLY);
	read(fd,arr,1000);
	printf("%c\n",arr[335]);

	*/

	if(argc != 5)
	{
		err(1,"Program must take four arguments\n");
	}

	int fd_f1_dat = open(argv[1],O_RDONLY);
	if(fd_f1_dat==-1)
	{
		err(1,"Couldn't open f1.dat file \n");
	}
	
	int fd_f1_idx = open(argv[2],O_RDONLY);
	if(fd_f1_idx==-1)
	{
		err(2,"Couldn't open f1.idx file\n");
	}
	int fd_f2_dat = open (argv[3],O_RDWR | O_CREAT | O_TRUNC , S_IRUSR | S_IWUSR);
	if(fd_f2_dat==-1)
	{
		err(3,"couldn't create and open f2.dat file \n");
	}
	int fd_f2_idx = open (argv[4],O_RDWR | O_CREAT | O_TRUNC , S_IRUSR | S_IWUSR);
	if(fd_f2_idx==-1)
	{
		err(3,"couldn't create and open f2.idx file \n");
	}
	
	struct stat f1_idx_stat,f1_dat_stat;
	if(stat(argv[2],&f1_idx_stat)==-1)
	{
		err(4,"Couldn't stat f1.idx file\n");
	}
	if(stat(argv[1],&f1_dat_stat)==-1)
	{
		err(7,"Couldn't stat f1.dat file");
	}
	if(f1_idx_stat.st_size % sizeof(idx_triple_t) != 0)
	{
		errx(5,"f1.idx is not with right size ( it has to devide 4 without reminder)\n");
	}

	idx_triple_t idx,f2_idx_backlog;
	uint8_t buff[256];
	int rd=0,f2_idx_count=0;

	while((rd=read(fd_f1_idx,&idx,sizeof(idx)))==sizeof(idx))
	{
		if(idx.offset >= f1_dat_stat.st_size)
		{
			errx(8,"It was provided an invalid offset in f1.idx file");
		}
		if(lseek(fd_f1_dat,idx.offset,SEEK_SET)==-1)
		{
			err(9,"Lseek seek set didn't work on f1.dat file");
		}
		if(idx.length == 0 )
		{
			warnx("String with 0 length in f1.idx file. Skipped ");
			continue;
		}
		if(read(fd_f1_dat,buff,idx.length)!=idx.length)
		{
			err(11,"Couldn't read string from f1.dat file");
		}



		//capital letter [A-Z]
		if(buff[0] >= 0x41 && buff[0] <= 0x5a)
		{
			f2_idx_backlog.offset=f2_idx_count;
			f2_idx_count+=idx.length;
			
			if(f2_idx_count >= UINT16_MAX )
			{
				warnx("Overflow max size of f2.idx ( uin16_t max is max allowed index)");

			}
			if(write(fd_f2_dat,buff,idx.length)!=idx.length)
			{
				err(12,"Couldn't write string in f2.dat file");
			}
			f2_idx_backlog.length=idx.length;
			f2_idx_backlog.reserved=0x00;


			if(write(fd_f2_idx,&f2_idx_backlog,sizeof(f2_idx_backlog))!=sizeof(f2_idx_backlog))
			{
				err(13,"coulnd't write backlog information in f2.idx file");
			}			
		}


		
	}
	if(rd==-1)
		{
			err(6,"Couldn't read from f1.idx file");
		}

	close(fd_f1_idx);
	close(fd_f1_dat);
	close(fd_f2_idx);
	close(fd_f2_dat);



	





}

