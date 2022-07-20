#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <err.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
struct pair
{
        uint32_t x;
        uint32_t y;
};


int main()
{
        int fd1=open("f1",O_RDONLY);
        if(fd1==-1)
        {	
          err(1,"Can't open f1 file");
				
        }
	
        int fd2=open("f2",O_RDONLY);
        if(fd2==-1)
        {
                err(1,"Couldn't open f2 file");
        }
		//something with stat (man stat). to take the size of f1 and f2 in bytes then i have to check whether f1 % 8 ==0 and f2 % 4 == 0 ( think why)
		struct stat statF1;
		int statusF1=stat("f1",&statF1);
		if(statusF1==-1)
		{
			err(1,"Couldn't use stat function on f1 file\n");
		}
		struct stat statF2;
		int statusF2=stat("f2",&statF2);
		if(statusF2==-1)
		{
			err(1,"couldn't use stat function on f2 file\n");
		}

		if(!(statF1.st_size % 8 == 0 && statF2.st_size % 4 == 0 ))
		{
			err(1,"Not a valid size of given f1 and f2 files [ f1 has to devide 8 without\
				remainder and f2 has to devide 4 without remainder]\n" );
		}


		

        int fd3=open("f3",O_CREAT | O_TRUNC | O_WRONLY, 0644);
        if(fd3==-1)
        {
                err(1,"Couldn't open the file");
        }

		
        struct pair pair_;
        pair_.x=0;
        pair_.y=0;
        uint32_t rn=0,c=0;
	//	uint64_t count=0;
        while((rn=read(fd1,&pair_,sizeof(pair_)))==sizeof(pair_))
        {
      //          printf("%d %d\n",pair_.x,pair_.y);
                int l=lseek(fd2,pair_.x*sizeof(pair_),SEEK_SET);
				if(l==-1)
				{
					err(1,"Couldn't lseek operate on f2 file\n");
				}
				//Here it must be pair_.y as a upper range delimiter , but right formattedfiles (f1,f2) wasn't provided
                for (uint32_t i=0;i<2;i++)
                {

                        if(read(fd2,&c,sizeof(c))==-1)
                        {
                                err(2,"couldn't read data");
                        }
		//				count+=sizeof(c);
                        if(write(fd3,&c,sizeof(c))==-1)
                        
                        {
                                err(3,"couldn'r write data");
                        }
                }

        }
		//printf("f3 size in bytes:%ld\n",count);
        close(fd1);
        close(fd2);
        close(fd3);

}


