#include <err.h>
#include <stdint.h>
#include <stdio.h>
  #include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>
#include <unistd.h>

int main (const int argc , const char * argv[])
{

	int fd=open(argv[1],O_RDONLY);
	if(fd==-1)
		{
			err(1,"Couldn't open\n");

		}
	int64_t num;
	read(fd,&num,sizeof(num));
	printf("%ld \n",num);
	close(fd);
}

