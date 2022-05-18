#include <stdlib.h>
#include <err.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <math.h>
#include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>


int main(const int argc, const char* argv[])
{
        if(argc!=3)
        {
                errx(1,"Program must take 2 arguments \n");
        }
        int fdDump=open(argv[2],O_RDONLY);
        if(fdDump==-1)
        {
                err(1,"Program couldn't open the given as argument binary file \n");
        }
        uint8_t num=0;
        if(strcmp(argv[1],"--min")==0)
        {
                uint8_t minNum=255;
                int read_size=0;
                while((read_size=read(fdDump,&num,sizeof(num))) > 0 )
                {
                        if(num<minNum)
                        {
                                minNum=num;
                        }
                }
                if(read_size==-1)
                {
                        err(1,"Couldn't read binary file in --min option\n");
                }
                printf("%d\n",minNum);
        /*if(write(1,&minNum,sizeof(minNum))==-1)
        {               err(1,"Program couldn't write minNum on stdout\n");
        }
        */

        }

        else if (strcmp(argv[1],"--max")==0)
        {
                uint8_t maxNum=0;
                int read_size=0;
                while((read_size=read(fdDump,&num,sizeof(num))) > 0 )
                {
                        if(num>maxNum)
                        {
                                maxNum=num;
                        }
                }
                if(read_size==-1)
                {
                        err(1,"Couldn't read binary file in --max option\n");
                }
                printf("%d\n",maxNum);



        }
        else if (strcmp(argv[1],"--print")==0)
        {
                int read_size=0,write_size=0;
                while((read_size=read(fdDump,&num,sizeof(num))) > 0 )
                {
                        printf("%d\n",num);
                }
                if(read_size==-1)
                {
                        err(1,"Couldn't read binary file in --print option\n");
                }

        }
        else
        {
                err(2,"None of known options was listed");
        }





        close(fdDump);



}

