#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
int main(const int argc,const char* argv[])
{
   int a=1000;
 
   if(fork())
   {
           a/=2;
           printf("%d\n",a);
   }
   else
   {
        if(fork())
        {
           a*=2;
           printf("%d\n",a);
           if(execlp("ls","ls","-l",(char*)NULL)==-1)
           {
              a=a+2;
              printf("%d\n",a);
           }
        }
        else
        {
                a+=2;
                printf("%d\n",a);
        }
   }
   a++;
   printf("%d\n",a);
}