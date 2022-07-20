
   #include <sys/types.h>
       #include <sys/stat.h>
    #include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>
     #include <unistd.h>
#include <err.h>
#include <stdint.h>
#include <stdio.h>
int main(const int argc, const char* argv[])
{
        if(argc!=2)
        {
                err(1,"Program must take an argmunt: operation \n");
        }
        int fd=open("mkio",O_RDONLY);
        if(fd==-1)
        {
                err(1,"couldn't open the pipe for read\n");
        }
        if(dup2(fd,0)==-1)
        {
                err(1,"couldn't read in the pipe\n");
        }
        if(execl(argv[1],argv[1],(char*)NULL)==-1)
        {
                close(fd);
                err(1,"couldn't exec %s\n",argv[1]);
        }
}


